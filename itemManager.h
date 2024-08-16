#ifndef ITEM_MANAGER_H 
#define ITEM_MANAGER_H

#include <unordered_map>
#include <string>
#include <sqlite3.h>
#include "Item.h"

class Item;

class ItemManager
{
public:
    ItemManager();
    ~ItemManager();

    bool addItem(const std::string &barcode, const std::string &manufacturer);
    Item *getItem(const std::string &barcode);
    bool updateItem(const std::string &barcode, const std::string &newManufacturer);
    bool deleteItem(const std::string &barcode);

private:
    std::unordered_map<std::string, std::unique_ptr<Item> > ItemMap;

    sqlite3 *db;

    void connectToDatabase();
    void saveItemToDatabase(const Item &item);
    void deleteItemFromDatabase(const std::string &barcode);
    Item *findItemByBarcode(const std::string &barcode);
};

#endif
