#ifndef CUSTOMER_MANAGER_H
#define CUSTOMER_MANAGER_H


//아래 세 헤더는 전부 직접 선언을 해 주어야 해서..네
#include <unordered_map>
#include <string>
#include <memory>

//using namespace std;

//사용자 지정 클래스에 대해 전방참조 테크닉을 쓸 수 있었군요 !
class Customer;

class CustomerManager{

public:
    CustomerManager();


    void printCustomer();
    void insertCustomer();
    int isEmpty();
    

    //void showCustomerInfo(Customer*);
    //


private:
    std::unordered_map<std::string,std::unique_ptr<Customer>> CustomerMap;
    unsigned int customerNumber;



};

#endif
