
#include "customerManager.h"
#include "customer.h"
#include <iostream>
#include <unordered_map>
//스마트포인터를 써서 실수를 줄여봅시다.
#include <memory>

using namespace std;

CustomerManager::CustomerManager():customerNumber(0){

}

int CustomerManager::isEmpty(){
    
    return customerNumber==0;
}

void CustomerManager::insertCustomer(unsigned int p_id, const string& p_name, const string& p_phone){

    //전화번호를 key 로 가지며, unique 스마트포인터에 동적할당된 Customer 객체가 리턴됩니다.
    CustomerMap.insert({p_phone,make_unique<Customer>(p_id,p_name,p_phone)});

    customerNumber++;
}

unique_ptr<Customer>& CustomerManager::searchCustomer(const string& p_phone){

    unique_ptr<Customer>& customer = CustomerMap[p_phone];

    return customer; 
} 


