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

void CustomerManager::insertCustomer(){

    unsigned int tmp_id;
    string tmp_name;
    string tmp_phone;

    cout<<"\n\n생성자는 id,이름,전번 순입니다. \n>>";
    cin>>tmp_id>>tmp_name>>tmp_phone;

    //전화번호를 key 로 가지며, unique 스마트포인터에 동적할당된 Customer 객체가 리턴됩니다.
    CustomerMap.insert({tmp_phone,make_unique<Customer>(tmp_id,tmp_name,tmp_phone)});

    customerNumber++;
}

void CustomerManager::printCustomer(){
    
    string tmp_name;

    cout<<"검색하고 싶은 사용자의 전화번호 4자리를 입력하세요\n>>";
    cin>>tmp_name;

    //unique ptr 의 특징 : 해당 포인터는 다른 객체가 소유해서 조작할 수는 없다..
    //하지만 참조자로 받아다가 사용하면 수정이 불가하셔서 합법이시다.
    unique_ptr<Customer>& customer = CustomerMap[tmp_name];

    cout<<"\n=================";
    cout<<"\n고객 id : "<<customer->getCustomerId();
    cout<<"\n고객 이름 : "<<customer->getCustomerName();
    cout<<"\n고객 전화번호 : "<<customer->getCustomerPhoneNumber()<<"\n";
}


