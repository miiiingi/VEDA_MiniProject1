#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <unordered_map>
#include <string>
#include <sqlite3.h>

#include <memory>        // For std::unique_ptr
#include <unordered_map> // For std::unordered_map
#include <fstream>
#include <sstream>

class Item;

class ItemManager
{
public:
    ItemManager(bool useInMemory = false);
    ~ItemManager();

    bool addItem(const std::string &barcode, const std::string &manufacturer, unsigned int price);
    Item *getItem(const std::string &barcode);
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    bool updateItem(const std::string &barcode, const std::string &newManufacturer, unsigned int newPrice);
    bool deleteItem(const std::string &barcode);
    void loadFromCSV(const std::string& filename);
    void saveToCSV(const std::string &filename);
    void getAllItem();

private:
    void connectToDatabase();
    void saveItemToDatabase(const Item &item);
    void deleteItemFromDatabase(const std::string &barcode);
    Item *findItemByBarcode(const std::string &barcode);

    sqlite3 *db = nullptr;
    std::unordered_map<std::string, std::unique_ptr<Item>> ItemMap;
    bool useInMemory = false;
};

#endif
