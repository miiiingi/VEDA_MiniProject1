#include <gtest/gtest.h>
#include "../include/itemManager.h"
#include "../include/item.h"

TEST(ItemManagerTest, AddItem) {
    ItemManager manager;

    // 새로운 상품 추가
    ASSERT_TRUE(manager.addItem("123456", "Samsung", 1000));

    // 추가된 상품 확인
    auto item = manager.getItem("123456");
    ASSERT_TRUE(item != nullptr);
    EXPECT_EQ(item->getbarcodeNumber(), "123456");
    EXPECT_EQ(item->getItemManufacturer(), "Samsung");
    EXPECT_EQ(item->getItemPrice(), 1000);
}

TEST(ItemManagerTest, GetItem) {
    ItemManager manager;
    manager.addItem("789012", "LG", 1500);

    // 존재하는 상품 검색
    auto item = manager.getItem("789012");
    ASSERT_TRUE(item != nullptr);
    EXPECT_EQ(item->getItemManufacturer(), "LG");

    // 존재하지 않는 상품 검색
    auto notFoundItem = manager.getItem("000000");
    EXPECT_TRUE(notFoundItem == nullptr);
}

TEST(ItemManagerTest, UpdateItem) {
    ItemManager manager;
    manager.addItem("345678", "Apple", 2000);

    // 상품 정보 업데이트
    ASSERT_TRUE(manager.updateItem("345678", "Apple Inc.", 2500));

    // 업데이트된 정보 확인
    auto item = manager.getItem("345678");
    ASSERT_TRUE(item != nullptr);
    EXPECT_EQ(item->getItemManufacturer(), "Apple Inc.");
    EXPECT_EQ(item->getItemPrice(), 2500);
}

TEST(ItemManagerTest, DeleteItem) {
    ItemManager manager;
    manager.addItem("901234", "Sony", 3000);

    // 상품 삭제
    ASSERT_TRUE(manager.deleteItem("901234"));

    // 삭제된 상품 확인
    auto item = manager.getItem("901234");
    EXPECT_TRUE(item == nullptr);
}
