#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>

class Item
{

public:
    Item(unsigned int itemId, const std::string &barcodeNumber, const std::string &manufacturer);

    void setItemId(const unsigned int id);
    unsigned int getItemId() const;

    void setbarcodeNumber(const std::string &barcode);
    const std::string &getbarcodeNumber() const;

    void setItemManufacturer(const std::string &manufacturer);
    const std::string &getItemManufacturer() const;

private:
    unsigned int itemId;
    std::string barcodeNumber;
    std::string itemManufacturer;
};

#endif
