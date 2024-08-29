#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<string>


class Customer{



public:
    Customer(const std::string&,const std::string&, unsigned int);

    void setCustomerName(const std::string&);
    const std::string& getCustomerName() const ;

    void setCustomerPhoneNumber(const std::string&);
    const std::string&  getCustomerPhoneNumber() const;

    void setCustomerPoint(const unsigned int);
    unsigned int getCustomerPoint() const;

private:
    //unsigned int customerId;
    std::string customerName;
    std::string customerPhoneNumber;
    unsigned int customerPoint;

};

#endif
