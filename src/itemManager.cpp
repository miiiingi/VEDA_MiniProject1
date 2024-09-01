#include "itemManager.h"
#include "item.h"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <sqlite3.h>
#include <fstream>
#include <sstream>

using namespace std;

ItemManager::ItemManager(bool useInMemory)
    : useInMemory(useInMemory) // 초기화 리스트에서 설정
{
    connectToDatabase();
}

ItemManager::~ItemManager()
{
    if (db)
    {
        sqlite3_close(db);
    }
}

void ItemManager::connectToDatabase()
{
    const char *dbPath = useInMemory ? ":memory:" : "itemdb.sqlite"; // 인메모리 또는 파일 DB 선택
    int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;  // 읽기/쓰기 및 파일이 없으면 생성
    int rc = sqlite3_open_v2(dbPath, &db, flags, nullptr);
    if (rc)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char *sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS Item ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "price INTEGER NOT NULL, "
        "barcode TEXT UNIQUE NOT NULL, "
        "manufacturer TEXT NOT NULL);";

    char *errMsg = nullptr;
    rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

bool ItemManager::addItem(const string &barcode, const std::string &manufacturer, unsigned int price)
{
    Item *item = findItemByBarcode(barcode);

    if (item)
    {
        return false;
    }

    const char *sqlInsert = "INSERT INTO Item (barcode, manufacturer, price) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, barcode.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, manufacturer.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, price);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "SQL error: Failed to insert item." << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);

    // 마지막으로 삽입된 행의 자동 증가 id를 가져옵니다.
    unsigned int newId = sqlite3_last_insert_rowid(db);

    // ItemMap에 추가합니다.
    ItemMap[barcode] = make_unique<Item>(newId, price, barcode, manufacturer);

    return true;
}

Item *ItemManager::getItem(const string &barcode)
{
    return findItemByBarcode(barcode);
}

void ItemManager::getAllItem()
{
    // 이미 열린 데이터베이스 연결을 사용합니다.
    const char *sql = "SELECT * FROM Item;";

    // 콜백 함수 호출
    char *zErrMsg = nullptr;
    int rc = sqlite3_exec(db, sql, ItemManager::callback, nullptr, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    else
    {
        std::cout << "All items retrieved successfully." << std::endl;
    }
}

bool ItemManager::updateItem(const string &barcode, const std::string &newManufacturer, unsigned int newPrice)
{
    Item *item = findItemByBarcode(barcode);
    if (item)
    {
        item->setItemManufacturer(newManufacturer);
        item->setItemPrice(newPrice);

        const char *sqlUpdate = "UPDATE Item SET manufacturer = ?, price = ? WHERE barcode = ?;";
        sqlite3_stmt *stmt;
        sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, 0);
        sqlite3_bind_text(stmt, 1, newManufacturer.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, newPrice);
        sqlite3_bind_text(stmt, 3, barcode.c_str(), -1, SQLITE_STATIC);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return true;
    }
    return false;
}

bool ItemManager::deleteItem(const string &barcode)
{
    Item *item = findItemByBarcode(barcode);
    if (item)
    {
        cout << "Item found in map and erased." << std::endl;
        deleteItemFromDatabase(barcode);
        return true;
    }
    return false;
}

void ItemManager::saveItemToDatabase(const Item &item)
{
    const char *sqlInsert = "INSERT INTO Item (id, barcode, manufacturer, price) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, item.getItemId());
    sqlite3_bind_text(stmt, 2, item.getbarcodeNumber().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, item.getItemManufacturer().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, item.getItemPrice());

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void ItemManager::deleteItemFromDatabase(const string &barcode)
{
    const char *sqlDelete = "DELETE FROM Item WHERE barcode = ?;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sqlDelete, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, barcode.c_str(), -1, SQLITE_STATIC);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}
void ItemManager::loadFromCSV(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // 데이터베이스 및 CustomerMap 초기화
    // 테이블을 삭제하고 새로 생성하여 기존 데이터를 초기화
    const char *sqlDropTable = "DROP TABLE IF EXISTS Item;";
    const char *sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS Item ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "price INTEGER NOT NULL, "
        "barcode TEXT UNIQUE NOT NULL, "
        "manufacturer TEXT NOT NULL);";

    char *errMsg = nullptr;

    // 테이블 삭제
    if (sqlite3_exec(db, sqlDropTable, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Failed to drop table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    }

    // 테이블 재생성
    if (sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Failed to create table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    }

    ItemMap.clear();

    std::string line;
    std::getline(file, line); // CSV 파일의 첫 줄은 헤더이므로 건너뜀

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, priceStr, barcode, manufacturer;

        if (!std::getline(ss, idStr, ',') ||
            !std::getline(ss, priceStr, ',') ||
            !std::getline(ss, barcode, ',') ||
            !std::getline(ss, manufacturer, ','))
        {
            std::cerr << "Malformed CSV line: " << line << std::endl;
            continue; // 잘못된 형식의 라인을 건너뜀
        }

        try
        {
            unsigned int id = std::stoi(idStr);
            unsigned int price = std::stoi(priceStr);

            // 데이터베이스에 고객 정보 삽입
            addItem(barcode, manufacturer, price);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Conversion error: " << e.what() << " in line: " << line << std::endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Out of range error: " << e.what() << " in line: " << line << std::endl;
        }
    }

    file.close();
}
void ItemManager::saveToCSV(const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << "id,price,barcode,manufacturer\n"; // CSV 헤더 작성
    const char *sqlSelect = "SELECT id, price, barcode, manufacturer FROM Item;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, 0);
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        unsigned int id = sqlite3_column_int(stmt, 0);
        unsigned int price = sqlite3_column_int(stmt, 1);
        std::string barcode = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        std::string manufacturer = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        // CSV 파일에 데이터 작성
        file << id << "," << price << "," << barcode << "," << manufacturer << "\n";
    }

    sqlite3_finalize(stmt);
    file.close();
}

Item *ItemManager::findItemByBarcode(const string &barcode)
{
    auto it = ItemMap.find(barcode);
    if (it != ItemMap.end())
    {
        return it->second.get();
    }

    const char *sqlSelect = "SELECT id, price, manufacturer FROM Item WHERE barcode = ?;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, barcode.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        unsigned int id = sqlite3_column_int(stmt, 0);
        unsigned int price = sqlite3_column_int(stmt, 1);
        string manufacturer = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

        ItemMap[barcode] = make_unique<Item>(id, price, barcode, manufacturer);
        sqlite3_finalize(stmt);
        return ItemMap[barcode].get();
    }

    sqlite3_finalize(stmt);
    return nullptr; // 해당 바코드의 상품이 없음
}
int ItemManager::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\t";
    }
    std::cout << std::endl;
    return 0;
}
