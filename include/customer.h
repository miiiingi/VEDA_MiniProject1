#ifndef CUSTOMER_H
#define CUSTOMER_H


//?꾨갑李몄“ ?뚰겕?됱쓣 ??蹂쇨퉴??
//?ㅽ뙣..而댄뙆?쇱씠 ?덈맗?덈떎. 萸붽? ambiguous ?섎떎?붾뜲 ??紐곌쿊?ㅼ슂.
//class string;
#include<string>


class Customer{



public:
    Customer(unsigned int,const std::string&,const std::string&, unsigned int);

    void setCustomerId(const unsigned int);
    unsigned int getCustomerId() const;

    void setCustomerName(const std::string&);
    const std::string& getCustomerName() const ;

    void setCustomerPhoneNumber(const std::string&);
    const std::string&  getCustomerPhoneNumber() const;

    void setCustomerPoint(const unsigned int);
    unsigned int getCustomerPoint() const;

private:
    unsigned int customerId;
    std::string customerName;
    std::string customerPhoneNumber;
    unsigned int customerPoint;
    //援щℓ?댁뿭? ?대뼸寃?援ъ꽦?섎㈃ 醫뗭쓣吏 ?꾩씠?붿뼱 ?꾩슂
    //?꾩씠???몄씪利덉젙蹂댁? / ?몃??뺣낫瑜?遺꾨━?덈떎怨??섏옄.

};

#endif