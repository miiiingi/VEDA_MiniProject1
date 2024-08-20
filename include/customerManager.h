
#ifndef CUSTOMER_MANAGER_H
#define CUSTOMER_MANAGER_H


//아래 세 헤더는 전부 직접 선언을 해 주어야 해서..네
#include <unordered_map>
#include <string>
#include <memory>


class Customer;

class CustomerManager{

public:
    CustomerManager();


    void insertCustomer(unsigned int,const std::string&, const std::string&);
    int isEmpty();

    //using 'auto' to get a return from this function can be useful. 
    std::unique_ptr<Customer>& searchCustomer(const std::string&);

private:
    std::unordered_map<std::string,std::unique_ptr<Customer>> CustomerMap;
    unsigned int customerNumber;


};

#endif
