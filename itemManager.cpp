#include "itemManager.h"
#include "item.h"
#include <sqlite3.h>

using namespace std;

ItemManager::ItemManager() {}

bool ItemManager::addItem(unsigned int id, const string &barcode, const string &manufacturer)
{
    if (ItemMap.find(barcode) != ItemMap.end())
    {
        return false; // 이미 존재하는 바코드 번호
    }
    ItemMap[barcode] = make_unique<Item>(id, barcode, manufacturer);
    return true;
}

Item *ItemManager::getItem(const string &barcode)
{
    return findItemByBarcode(barcode);
}

bool ItemManager::updateItem(const string &barcode, unsigned int newId, const string &newManufacturer)
{
    Item *item = findItemByBarcode(barcode);
    if (item)
    {
        item->setItemId(newId);
        item->setItemManufacturer(newManufacturer);
        return true;
    }
    return false;
}

bool ItemManager::deleteItem(const string &barcode)
{
    return ItemMap.erase(barcode) > 0;
}

Item *ItemManager::findItemByBarcode(const string &barcode)
{
    auto it = ItemMap.find(barcode);
    if (it != ItemMap.end())
    {
        return it->second.get();
    }
    return nullptr; // 해당 바코드의 상품이 없음
}