#include "mainMenu.h"
#include "customer.h"
#include "itemManager.h"
#include "item.h"

#include <iostream>

using namespace std;

void MainMenu::run()
{
    int choice = 0;
    do
    {
        showMainMenu();
        cin >> choice;
        handleMainMenuChoice(choice);
    } while (choice != 4);
}

void MainMenu::showMainMenu()
{
    cout << "\n=== Welcome to VEDA mall ===" << endl;
    cout << "1. Customer" << endl;
    cout << "2. Item" << endl;
    cout << "3. T.B.D" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice >> ";
}

void MainMenu::handleMainMenuChoice(int choice)
{
    switch (choice)
    {
    case 1:
        showCustomerMenu();
        break;
    case 2:
        showItemMenu();
        break;
    case 3:
        cout << "to be determined ..." << endl;
        break;
    case 4:
        cout << "Exiting..." << endl;
        return;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}

void MainMenu::showCustomerMenu()
{
    int choice = 0;
    do
    {
        cout << "\n=== Customer Menu ===" << endl;
        cout << "1. Insert Customer" << endl;
        cout << "2. Search Customer" << endl;
        cout << "3. Modify Customer" << endl;
        cout << "4. Delete Customer" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice >> ";
        cin >> choice;
        handleCustomerMenuChoice(choice);
    } while (choice != 5);
}

void MainMenu::handleCustomerMenuChoice(int choice)
{
    switch (choice)
    {
    case 1:
    { // 1. Insert Costomer
        unsigned int id, point;
        string name, phone;

        cout << "Insert ID, NAME, PHONE NUMBER, POINT >> " << endl;
        cin >> id >> name >> phone>>point;

        customerManager.insertCustomer(id, name, phone, point);
        cout << "Successfully added customer information" << endl;
        break;
    }
    case 2:
    { // 2. Search Customer
        string phone;
        cout << "Enter customer phone number to search >> " << endl;
        cin >> phone;

        unique_ptr<Customer> &customer = customerManager.searchCustomer(phone);

        if (customer)
        {
            cout << "Customer Found" << endl;
            cout << "ID: " << customer->getCustomerId() << endl;
            cout << "Name: " << customer->getCustomerName() << endl;
            cout << "Phone: " << customer->getCustomerPhoneNumber() << endl;
	    cout << "Point : " << customer->getCustomerPoint() << endl;
        }
        else
        {
            cout << "Customer not found ..." << endl;
        }
        break;
    }
    case 3:
    {
        string phone;
        cout << "Enter customer phone number to modify >> " << endl;
        cin >> phone;

        unique_ptr<Customer> &customer = customerManager.searchCustomer(phone);

        unsigned int point;
	//n_phone 은 검색 key phone 과 구분되는, 새 phone 입니다.
        string name,n_phone;


        cout << "Insert new NAME, PHONE NUMBER, POINT >> " << endl;
        cin >> name >> n_phone>>point;


        if (customer)
        {
	    cout << "Customer Update Successful" << endl;
	    customerManager.updateCustomer(phone,name,n_phone,point);
        }
        else
        {
            cout << "Customer not found ..." << endl;
        }
        break;
    }
    case 4:
    {	
        string phone;
        cout << "Enter customer phone number to delete >> " << endl;
        cin >> phone;

        unique_ptr<Customer> &customer = customerManager.searchCustomer(phone);

        if (customer)
        {
            cout << "Customer Successfully deleted" << endl;

	    customerManager.deleteCustomer(phone);
        }
        else
        {
            cout << "Customer not found ..." << endl;
        }
        break;
    }
    case 5:
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}

void MainMenu::showItemMenu()
{
    int choice = 0;
    do
    {
        cout << "\n=== Item Menu ===" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Get Item" << endl;
        cout << "3. Update Item" << endl;
        cout << "4. Delete Item" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice >> ";
        cin >> choice;
        handleItemMenuChoice(choice);
    } while (choice != 5);
}

void MainMenu::handleItemMenuChoice(int choice)
{
    string barcode, manufacturer;
    ItemManager itemManager;
    Item *item;
    switch (choice)
    {
    case 1:
        cout << "Type barcode and manufacturer >> ";
        cin >> barcode >> manufacturer;
        if (itemManager.addItem(barcode, manufacturer))
        {
            cout << "Added Barcode: " << barcode;
        }
        else
        {
            cout << "Item not found. Returning to Item Menu..." << endl;
            showItemMenu(); // 메뉴를 다시 출력
        }
        break;
    case 2:
        cout << "Type barcode >> ";
        cin >> barcode;
        item = itemManager.getItem(barcode);
        if (item)
        {
            cout << "Barcode: " << item->getbarcodeNumber() << endl;
            cout << "Manufacturer: " << item->getItemManufacturer();
        }
        else
        {
            cout << "Item not found. Returning to Item Menu..." << endl;
            showItemMenu(); // 메뉴를 다시 출력
        }
        break;
    case 3:
        cout << "Type barcode and manufacturer >> ";
        cin >> barcode >> manufacturer;
        if (itemManager.updateItem(barcode, manufacturer))
        {
            cout << "Updated Barcode: " << barcode;
        }
        else
        {
            cout << "Item not found. Returning to Item Menu..." << endl;
            showItemMenu(); // 메뉴를 다시 출력
        }
        break;
    case 4:
        cout << "Type barcode >> ";
        cin >> barcode;
        if (itemManager.deleteItem(barcode))
        {
            cout << "Deleted Barcode: " << barcode;
        }
        else
        {
            cout << "Item not found. Returning to Item Menu..." << endl;
            showItemMenu(); // 메뉴를 다시 출력
        }
        break;
    case 5:
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}
