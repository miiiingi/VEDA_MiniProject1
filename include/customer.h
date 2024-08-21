#ifndef CUSTOMER_H
#define CUSTOMER_H


//전방참조 테크닉을 써 볼까요?
//실패..컴파일이 안됩니다. 뭔가 ambiguous 하다는데 잘 몰겟네요.
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
    //구매내역은 어떻게 구성하면 좋을지 아이디어 필요
    //아이템 세일즈정보와 / 세부정보를 분리했다고 하자.

};

#endif
