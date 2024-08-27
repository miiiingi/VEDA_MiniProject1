
#ifndef CUSTOMER_MANAGER_H
#define CUSTOMER_MANAGER_H


//아래 세 헤더는 전부 직접 선언을 해 주어야 해서..네
#include <unordered_map>
#include <string>
#include <memory>
#include <sqlite3.h>

class Customer;

class CustomerManager{

public:
    CustomerManager(bool useInMemory = false);
    ~CustomerManager();

    void insertCustomer(const std::string&, const std::string&);
    int isEmpty();

    //using 'auto' to get a return from this function can be useful. 
    std::unique_ptr<Customer>& searchCustomer(const std::string&);
    
    void updateCustomer(const std::string& p_phone, const std::string& new_name, const std::string& new_phone, const unsigned int);
    void deleteCustomer(const std::string& p_phone); 

private:
    sqlite3* db;
    std::unordered_map<std::string,std::unique_ptr<Customer>> CustomerMap;
    bool useInMemory = false;
    unsigned int customerNumber;

};

#endif
