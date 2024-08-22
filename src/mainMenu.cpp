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
    } while (choice != 3); 
}

void MainMenu::showMainMenu()
{
    cout << "\n=== Welcome to VEDA mall ===" << endl;
    cout << "1. Customer" << endl;
    cout << "2. Manager" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice >> ";
}

void MainMenu::handleMainMenuChoice(int choice)
{
    switch (choice)
    {
    case 1:
        if (loginCustomer()) 
        {
            showCustomerMenu();
        }
        break;
    case 2:
        showManagerMenu();
        break;
    case 3:
        cout << "Exiting..." << endl;
        return;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}

bool MainMenu::loginCustomer()
{
    string phone;
    cout << "\nEnter your phone number to login >> ";
    cin >> phone;

    unique_ptr<Customer> &customer = customerManager.searchCustomer(phone);

    if (customer)
    {
        cout << "Login successful. Welcome, " << customer->getCustomerName() << "!" << endl;
        currentCustomer = customer.get(); 
        return true;
    }
    else
    {
        cout << "Login failed. Customer not found." << endl;
        return false;
    }
}

void MainMenu::showCustomerMenu()
{
    int choice = 0;
    do
    {
        cout << "\n=== Customer Menu ===" << endl;
        cout << "1. View Items" << endl;
        cout << "2. Purchase Items" << endl;
        cout << "3. View Points" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice >> ";
        cin >> choice;
        handleCustomerMenuChoice(choice);
    } while (choice != 4); 
}

void MainMenu::handleCustomerMenuChoice(int choice)
{
    switch (choice)
    {
    case 1:
        cout << "Viewing items (T.B.D)..." << endl;
        break;
    case 2:
        cout << "Purchasing items (T.B.D)..." << endl;
        break;
    case 3:
        cout << "Viewing points (T.B.D)..." << endl;
        break;
    case 4:
        cout << "Logging out..." << endl;
        currentCustomer = nullptr; 
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}

void MainMenu::showManagerMenu()
{
    int choice = 0;
    do
    {
        cout << "\n=== Manager Menu ===" << endl;
        cout << "1. Customer Management" << endl;
        cout << "2. Item Management" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice >> ";
        cin >> choice;
        handleManagerMenuChoice(choice);
    } while (choice != 3); 
}

void MainMenu::handleManagerMenuChoice(int choice)
{
    switch (choice)
    {
    case 1:
        showCustomerManagementMenu(); 
        break;
    case 2:
        showItemManagementMenu(); 
        break;
    case 3:
        cout << "Returning to Main Menu..." << endl;
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}

void MainMenu::showCustomerManagementMenu()
{
    int choice = 0;
    do
    {
        cout << "\n=== Customer Management ===" << endl;
        cout << "1. Insert Customer" << endl;
        cout << "2. Search Customer" << endl;
        cout << "3. Update Customer" << endl;
        cout << "4. Delete Customer" << endl;
        cout << "5. Back to Manager Menu" << endl;
        cout << "Enter your choice >> ";
        cin >> choice;
        handleCustomerManagementMenuChoice(choice);
    } while (choice != 5); // 5. Back to Manager Menu 선택 시 종료
}

void MainMenu::handleCustomerManagementMenuChoice(int choice)
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
            cout << "Returning to Manager Menu..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

void MainMenu::showItemManagementMenu()
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
        handleItemManagementMenu(choice);
    } while (choice != 5);
}

void MainMenu::handleItemManagementMenu(int choice)
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
            showItemManagementMenu(); 
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
            showItemManagementMenu(); 
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
            showItemManagementMenu(); 
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
            showItemManagementMenu(); 
        }
        break;
    case 5:
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}
