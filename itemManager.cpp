#include "ItemManager.h"
#include "Item.h"
#include <iostream>
#include <memory>

ItemManager::ItemManager()
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
    int rc = sqlite3_open("itemdb.sqlite", &db);
    if (rc)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char *sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS Item ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "barcode TEXT UNIQUE NOT NULL, "
        "manufacturer TEXT NOT NULL);";

    char *errMsg = nullptr;
    rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

bool ItemManager::addItem(const std::string &barcode, const std::string &manufacturer)
{
    if (ItemMap.find(barcode) != ItemMap.end())
    {
        return false; // 이미 존재하는 바코드 번호
    }

    const char *sqlInsert = "INSERT INTO Item (barcode, manufacturer) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, barcode.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, manufacturer.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        std::cerr << "SQL error: Failed to insert item." << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);

    // 마지막으로 삽입된 행의 자동 증가 id를 가져옵니다.
    unsigned int newId = sqlite3_last_insert_rowid(db);

    // ItemMap에 추가합니다.
    ItemMap[barcode] = std::make_unique<Item>(newId, barcode, manufacturer);

    return true;
}

Item *ItemManager::getItem(const std::string &barcode)
{
    return findItemByBarcode(barcode);
}

bool ItemManager::updateItem(const std::string &barcode, const std::string &newManufacturer)
{
    Item *item = findItemByBarcode(barcode);
    if (item)
    {
        item->setItemManufacturer(newManufacturer);

        const char *sqlUpdate = "UPDATE Item SET manufacturer = ? WHERE barcode = ?;";
        sqlite3_stmt *stmt;
        sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, 0);
        sqlite3_bind_text(stmt, 1, newManufacturer.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, barcode.c_str(), -1, SQLITE_STATIC);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return true;
    }
    return false;
}

bool ItemManager::deleteItem(const std::string &barcode)
{
    if (ItemMap.erase(barcode) > 0)
    {
        deleteItemFromDatabase(barcode);
        return true;
    }
    return false;
}

void ItemManager::saveItemToDatabase(const Item &item)
{
    const char *sqlInsert = "INSERT INTO Item (id, barcode, manufacturer) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, item.getItemId());
    sqlite3_bind_text(stmt, 2, item.getbarcodeNumber().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, item.getItemManufacturer().c_str(), -1, SQLITE_STATIC);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void ItemManager::deleteItemFromDatabase(const std::string &barcode)
{
    const char *sqlDelete = "DELETE FROM Item WHERE barcode = ?;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sqlDelete, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, barcode.c_str(), -1, SQLITE_STATIC);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

Item *ItemManager::findItemByBarcode(const std::string &barcode)
{
    auto it = ItemMap.find(barcode);
    if (it != ItemMap.end())
    {
        return it->second.get();
    }

    const char *sqlSelect = "SELECT id, manufacturer FROM Item WHERE barcode = ?;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, barcode.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        unsigned int id = sqlite3_column_int(stmt, 0);
        std::string manufacturer = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        ItemMap[barcode] = std::make_unique<Item>(id, barcode, manufacturer);
        sqlite3_finalize(stmt);
        return ItemMap[barcode].get();
    }

    sqlite3_finalize(stmt);
    return nullptr; // 해당 바코드의 상품이 없음
}
