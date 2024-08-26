#ifndef ITEM_MANAGER_H 
#define ITEM_MANAGER_H

#include <unordered_map>
#include <string>
#include <sqlite3.h>

#include <memory>           // For std::unique_ptr
#include <unordered_map>   // For std::unordered_map

class Item;

class ItemManager
{
public:
    ItemManager();
    ~ItemManager();

    bool addItem(const std::string &barcode, const std::string &manufacturer, unsigned int price);
    Item *getItem(const std::string &barcode);
    void getAllItem();
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    bool updateItem(const std::string &barcode, const std::string &newManufacturer, unsigned int newPrice);
    bool deleteItem(const std::string &barcode);

private:
    std::unordered_map<std::string, std::unique_ptr<Item>> ItemMap;

    sqlite3 *db;

    void connectToDatabase();
    void saveItemToDatabase(const Item &item);
    void deleteItemFromDatabase(const std::string &barcode);
    Item *findItemByBarcode(const std::string &barcode);
};

#endif
