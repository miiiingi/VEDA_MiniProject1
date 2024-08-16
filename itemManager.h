#ifndef CUSTOMER_MANAGER_H
#define CUSTOMER_MANAGER_H

#include <unordered_map>
#include <string>

class Item;

class ItemManager
{
public:
    ItemManager();

    bool addItem(unsigned int id, const std::string &barcode, const std::string &manufacturer);
    Item *getItem(const std::string &barcode);
    bool updateItem(const std::string &barcode, unsigned int newId, const std::string &newManufacturer);
    bool deleteItem(const std::string &barcode);

private:
    std::unordered_map<std::string, std::unique_ptr<Item>> ItemMap;
    Item *findItemByBarcode(const std::string &barcode);
};

#endif
