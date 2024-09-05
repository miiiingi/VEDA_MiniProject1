#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item
{

public:
    Item(unsigned int itemId, unsigned int itemPrice, const std::string &barcodeNumber, const std::string &manufacturer);

    void setItemId(const unsigned int id);
    unsigned int getItemId() const;

    void setItemPrice(const unsigned int price);
    unsigned int getItemPrice() const;

    void setbarcodeNumber(const std::string &barcode);
    const std::string &getbarcodeNumber() const;

    void setItemManufacturer(const std::string &manufacturer);
    const std::string &getItemManufacturer() const;

private:
    unsigned int itemId;
    unsigned int itemPrice;
    std::string barcodeNumber;
    std::string itemManufacturer;
};

#endif