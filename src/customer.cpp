#include <iostream>
#include "customer.h"

using namespace std;

Customer::Customer(const string& p_name,const string& p_phone, unsigned int p_point):customerName(p_name),customerPhoneNumber(p_phone), customerPoint(p_point){
    cout<<"Customer "<<customerPhoneNumber<<" added to the list\n";


}

/*
void Customer::setCustomerId(const unsigned int p_id){
    customerId = p_id;
}

unsigned int Customer::getCustomerId() const{
    return customerId;
}
*/

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
