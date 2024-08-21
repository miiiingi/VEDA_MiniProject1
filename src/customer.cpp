//include 의 순서에 대해 : Qt 에서는, 기본적으로 사용자 지정 라이브러리를 먼저 include 합니다만, C/C++ 에서는 일단 표준 라이브러리들을 우선 include 하는 줄로 전 알고 있습니다. 경우에 따라 이 순서가 정상적인 컴파일에 영향을 주는 경우도 있다고 하네요.
#include <iostream>
//벡터의 경우 헤더에서 이미 include 했습니다.
//헤더파일 이름을 대문자로 해야했던가 ?? 싶네요. 자바에선 그렇게 했던 것 같은데..
#include "customer.h"

using namespace std;

Customer::Customer(unsigned int p_id, const string& p_name,const string& p_phone, unsigned int p_point):customerId(p_id),customerName(p_name),customerPhoneNumber(p_phone), customerPoint(p_point){
    cout<<"Customer "<<customerPhoneNumber<<" added to the list\n";


}

void Customer::setCustomerId(const unsigned int p_id){
    customerId = p_id;
}

unsigned int Customer::getCustomerId() const{
    return customerId;
}

//사이즈가 커질 수 있는 parameter & return 은 무조건 const 참조자로 사용했습니다.
void Customer::setCustomerName(const string& p_name){
    customerName = p_name;
}

const string& Customer::getCustomerName() const{
    return customerName;
}

void Customer::setCustomerPhoneNumber(const string& p_phone){
    customerPhoneNumber = p_phone;
}

const string& Customer::getCustomerPhoneNumber()const{
    return customerPhoneNumber;
}

void Customer::setCustomerPoint(unsigned int p_point){
    customerPoint = p_point;
}

unsigned int Customer::getCustomerPoint() const{
    return customerPoint;
}

