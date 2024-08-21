#include "item.h"

using namespace std;

Item::Item(unsigned int id, const string &barcode, const string &manufacturer)
    : itemId(id), barcodeNumber(barcode), itemManufacturer(manufacturer) {}

void Item::setItemId(const unsigned int id)
{
    itemId = id;
}
unsigned int Item::getItemId() const
{
    return itemId;
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