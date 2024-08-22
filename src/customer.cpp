//include ???쒖꽌?????: Qt ?먯꽌?? 湲곕낯?곸쑝濡??ъ슜??吏???쇱씠釉뚮윭由щ? 癒쇱? include ?⑸땲?ㅻ쭔, C/C++ ?먯꽌???쇰떒 ?쒖? ?쇱씠釉뚮윭由щ뱾???곗꽑 include ?섎뒗 以꾨줈 ???뚭퀬 ?덉뒿?덈떎. 寃쎌슦???곕씪 ???쒖꽌媛 ?뺤긽?곸씤 而댄뙆?쇱뿉 ?곹뼢??二쇰뒗 寃쎌슦???덈떎怨??섎꽕??
#include <iostream>
//踰≫꽣??寃쎌슦 ?ㅻ뜑?먯꽌 ?대? include ?덉뒿?덈떎.
//?ㅻ뜑?뚯씪 ?대쫫???臾몄옄濡??댁빞?덈뜕媛 ?? ?띕꽕?? ?먮컮?먯꽑 洹몃젃寃??덈뜕 寃?媛숈???.
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

//?ъ씠利덇? 而ㅼ쭏 ???덈뒗 parameter & return ? 臾댁“嫄?const 李몄“?먮줈 ?ъ슜?덉뒿?덈떎.
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
