
#include "customerManager.h"
#include "customer.h"
#include <iostream>
#include <unordered_map>
#include <memory>

using namespace std;

CustomerManager::CustomerManager() : customerNumber(0), db(nullptr) {
    int rc = sqlite3_open("customerdb.sqlite", &db);
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
        "point INTEGER DEFAULT 0);";  // 'point' 열 추가

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

void CustomerManager::insertCustomer(unsigned int p_id, const string& p_name, const string& p_phone, unsigned int p_point) {
    const char* sqlInsert = "INSERT INTO Customer (id, name, phone, point) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, p_id);
    sqlite3_bind_text(stmt, 2, p_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, p_phone.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, p_point);  // 'point' 값 추가

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        CustomerMap[p_phone] = std::make_unique<Customer>(p_id, p_name, p_phone, p_point); // 'point' 값 추가
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
            CustomerMap[phone] = std::make_unique<Customer>(id, name, phone, point);  // 'point' 값 추가
        }

        sqlite3_finalize(stmt);
    }
    return CustomerMap[p_phone];
}

void CustomerManager::updateCustomer(const std::string& p_phone, const std::string& new_name, const std::string& new_phone, unsigned int new_point) {
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

CustomerManager::~CustomerManager() {
    if (db) {
        sqlite3_close(db);
    }
}

