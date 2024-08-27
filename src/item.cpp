#include "item.h"

using namespace std;

Item::Item(unsigned int id, unsigned int price, const string &barcode, const string &manufacturer)
    : itemId(id), barcodeNumber(barcode), itemManufacturer(manufacturer), itemPrice(price)  {}

void Item::setItemId(const unsigned int id)
{
    itemId = id;
}
unsigned int Item::getItemId() const
{
    return itemId;
}

void Item::setItemPrice(const unsigned int price)
{
    itemPrice = price;
}
unsigned int Item::getItemPrice() const
{
    return itemPrice;
}

void Item::setbarcodeNumber(const string &barcode)
{
    barcodeNumber = barcode;
}
const string &Item::getbarcodeNumber() const
{
    return barcodeNumber;
}

void Item::setItemManufacturer(const string &manufacturer)
{
    itemManufacturer = manufacturer;
}
const string &Item::getItemManufacturer() const
{
    return itemManufacturer;
}