#include <gtest/gtest.h>
#include "customerManager.h"
#include "customer.h"

TEST(CustomerManagerTest, InsertCustomer) {
    CustomerManager manager;

    // 새로운 고객 추가
    manager.insertCustomer("Alice", "010-1234-5678");

    // 추가된 고객 확인
    auto& customer = manager.searchCustomer("010-1234-5678");
    ASSERT_TRUE(customer != nullptr);
    EXPECT_EQ(customer->getCustomerName(), "Alice");
    EXPECT_EQ(customer->getCustomerPhoneNumber(), "010-1234-5678");
}

TEST(CustomerManagerTest, SearchCustomer) {
    CustomerManager manager;
    manager.insertCustomer("Bob", "010-9876-5432");

    // 존재하는 고객 검색
    auto& customer = manager.searchCustomer("010-9876-5432");
    ASSERT_TRUE(customer != nullptr);
    EXPECT_EQ(customer->getCustomerName(), "Bob");

    // 존재하지 않는 고객 검색
    auto& notFoundCustomer = manager.searchCustomer("010-0000-0000");
    EXPECT_TRUE(notFoundCustomer == nullptr);
}

TEST(CustomerManagerTest, UpdateCustomer) {
    CustomerManager manager;
    manager.insertCustomer("Charlie", "010-1111-2222");

    // 고객 정보 업데이트
    manager.updateCustomer("010-1111-2222", "Charles", "010-3333-4444", 100);

    // 업데이트된 정보 확인
    auto& customer = manager.searchCustomer("010-3333-4444");
    ASSERT_TRUE(customer != nullptr);
    EXPECT_EQ(customer->getCustomerName(), "Charles");
    EXPECT_EQ(customer->getCustomerPhoneNumber(), "010-3333-4444");
    EXPECT_EQ(customer->getCustomerPoint(), 100);
}

TEST(CustomerManagerTest, DeleteCustomer) {
    CustomerManager manager;
    manager.insertCustomer("David", "010-5555-6666");

    // 고객 삭제
    manager.deleteCustomer("010-5555-6666");

    // 삭제된 고객 확인
    auto& customer = manager.searchCustomer("010-5555-6666");
    EXPECT_TRUE(customer == nullptr);
}
