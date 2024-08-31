#include "customerManager.h"
#include "customer.h"
#include "itemManager.h"
#include "item.h"

#include <iostream>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <sstream>


using namespace std;

CustomerManager::CustomerManager(bool useInMemory) : customerNumber(0), db(nullptr), useInMemory(useInMemory) {
    const char *dbPath = useInMemory ? ":memory:" : "customerdb.sqlite"; // 인메모리 또는 파일 DB 선택
    int rc = sqlite3_open(dbPath, &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // 테이블 생성 SQL 쿼리
    const char *sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS Customer ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "phone TEXT UNIQUE NOT NULL, "
        "point INTEGER DEFAULT 0);";  // point' 열 추가

    // 테이블 생성 실행
    char *errMsg = nullptr;
    rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

int CustomerManager::isEmpty(){
    return customerNumber == 0;
}

void CustomerManager::insertCustomer(const string& p_name, const string& p_phone) {
    // 중복 확인 쿼리
    const char* sqlCheck = "SELECT COUNT(*) FROM Customer WHERE phone = ?;";
    sqlite3_stmt* checkStmt;
    sqlite3_prepare_v2(db, sqlCheck, -1, &checkStmt, 0);
    sqlite3_bind_text(checkStmt, 1, p_phone.c_str(), -1, SQLITE_STATIC);

    // 중복된 고객 존재 시
    if (sqlite3_step(checkStmt) == SQLITE_ROW && sqlite3_column_int(checkStmt, 0) > 0) {
        std::cerr << "Customer with phone number already exists: " << p_phone << std::endl;
        sqlite3_finalize(checkStmt);
        return;
    }
    sqlite3_finalize(checkStmt);

    const char* sqlInsert = "INSERT INTO Customer (name, phone) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, p_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, p_phone.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        CustomerMap[p_phone] = std::make_unique<Customer>(p_name, p_phone,0); // 'point' 값 추가
        customerNumber++;
    } else {
        std::cerr << "Failed to insert customer: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

unique_ptr<Customer>& CustomerManager::searchCustomer(const string& p_phone){
    auto it = CustomerMap.find(p_phone);
    if (it == CustomerMap.end()) {
        const char* sqlSelect = "SELECT id, name, phone, point FROM Customer WHERE phone = ?;";  // 'point' 추가
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, 0);
        sqlite3_bind_text(stmt, 1, p_phone.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            unsigned int id = sqlite3_column_int(stmt, 0);
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            unsigned int point = sqlite3_column_int(stmt, 3);  // 'point' 값 추가
            CustomerMap[phone] = std::make_unique<Customer>(name, phone, point);  // 'point' 값 추가
        }

        sqlite3_finalize(stmt);
    }
    return CustomerMap[p_phone];
}

void CustomerManager::updateCustomer(const std::string& p_phone, const std::string& new_name, const std::string& new_phone, unsigned int new_point) {

    // 고객 존재 여부 확인 쿼리
    const char* sqlCheck = "SELECT COUNT(*) FROM Customer WHERE phone = ?;";
    sqlite3_stmt* checkStmt;
    sqlite3_prepare_v2(db, sqlCheck, -1, &checkStmt, 0);
    sqlite3_bind_text(checkStmt, 1, p_phone.c_str(), -1, SQLITE_STATIC);

    // 고객이 존재하지 않는 경우
    if (sqlite3_step(checkStmt) == SQLITE_ROW && sqlite3_column_int(checkStmt, 0) == 0) {
        std::cerr << "Customer with phone number does not exist: " << p_phone << std::endl;
        sqlite3_finalize(checkStmt);
        return;
    }
    sqlite3_finalize(checkStmt);


    const char* sqlUpdate = "UPDATE Customer SET name = ?, phone = ?, point = ? WHERE phone = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, new_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, new_phone.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, new_point);  // 'point' 값 추가
    sqlite3_bind_text(stmt, 4, p_phone.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        auto it = CustomerMap.find(p_phone);
        if (it != CustomerMap.end()) {
            it->second->setCustomerName(new_name);
            it->second->setCustomerPhoneNumber(new_phone);
            it->second->setCustomerPoint(new_point);  // 'point' 값 업데이트
            CustomerMap[new_phone] = std::move(it->second); // 이전 데이터를 삭제 및 새로 생성
            CustomerMap.erase(it);
        }
    } else {
        std::cerr << "Failed to update customer: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void CustomerManager::deleteCustomer(const std::string& p_phone) {
    const char* sqlDelete = "DELETE FROM Customer WHERE phone = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqlDelete, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, p_phone.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        CustomerMap.erase(p_phone);
        customerNumber--;
    } else {
        std::cerr << "Failed to delete customer: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void CustomerManager::saveToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << "id,name,phone,point\n";  // CSV 헤더 작성
    const char* sqlSelect = "SELECT id, name, phone, point FROM Customer;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, 0);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        unsigned int id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        unsigned int point = sqlite3_column_int(stmt, 3);
        // CSV 파일에 데이터 작성
        file << id << "," << name << "," << phone << "," << point << "\n";
    }
    sqlite3_finalize(stmt);
    file.close();
}


void CustomerManager::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // 데이터베이스 및 CustomerMap 초기화
    // 테이블을 삭제하고 새로 생성하여 기존 데이터를 초기화
    const char* sqlDropTable = "DROP TABLE IF EXISTS Customer;";
    const char* sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS Customer ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "phone TEXT UNIQUE NOT NULL, "
        "point INTEGER DEFAULT 0);";

    char* errMsg = nullptr;

    // 테이블 삭제
    if (sqlite3_exec(db, sqlDropTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Failed to drop table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    }

    // 테이블 재생성
    if (sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Failed to create table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    }

    // CustomerMap 초기화
    CustomerMap.clear();
    customerNumber = 0;

    std::string line;
    std::getline(file, line);  // CSV 파일의 첫 줄은 헤더이므로 건너뜀

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, phone, pointStr;

        if (!std::getline(ss, idStr, ',') ||
            !std::getline(ss, name, ',') ||
            !std::getline(ss, phone, ',') ||
            !std::getline(ss, pointStr, ',')) {
            std::cerr << "Malformed CSV line: " << line << std::endl;
            continue;  // 잘못된 형식의 라인을 건너뜀
        }

        try {
            unsigned int id = std::stoi(idStr);
            unsigned int point = std::stoi(pointStr);

            // 데이터베이스에 고객 정보 삽입
            insertCustomer(name, phone);
            updateCustomer(phone, name, phone, point);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Conversion error: " << e.what() << " in line: " << line << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range error: " << e.what() << " in line: " << line << std::endl;
        }
    }

    file.close();
}

void CustomerManager::purchaseItem(const string& phone, const string& barcode, ItemManager& itemMgr){
    //바코드로 item 검색해서 item 유니크포인터 참조자 획득 -> price 를 게터로 받아온다.
    Item* targetItem(itemMgr.getItem(barcode));

    //받아온 price 기반으로 가산해야 하는 포인트 계산
    unsigned int targetPrice(targetItem->getItemPrice());

    //업데이트 해줘야하는 고객을 get
    unique_ptr<Customer>& targetCustomer(searchCustomer(phone));

    
    const char* sqlUpdatePoint = "UPDATE Customer SET point = ? WHERE phone = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqlUpdatePoint, -1, &stmt, 0);
    sqlite3_bind_int(stmt,1,targetPrice*0.01+targetCustomer->getCustomerPoint());
    sqlite3_bind_text(stmt, 2, phone.c_str(),-1,SQLITE_STATIC);  // 'point' 값 추가

    //이후, map / sql 파일에 업데이트하고 종료
    
    if (sqlite3_step(stmt) == SQLITE_DONE) {
	targetCustomer->setCustomerPoint(targetPrice*0.01+targetCustomer->getCustomerPoint());
    } else {
        std::cerr << "Failed to update customer: " << sqlite3_errmsg(db) << std::endl;
    }
}   

CustomerManager::~CustomerManager() {
    if (db) {
        sqlite3_close(db);
    }
}
