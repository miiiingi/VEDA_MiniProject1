#include "mainMenu.h"
#include "customer.h"
#include "itemManager.h"
#include "item.h"

#include <iostream>

using namespace std;

int MainMenu::getUserInput()
{
    int choice;
    while(true)
    {
        cin >> choice;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number" << endl;
            cout << "Retry enter a number >> " << endl;
        }
        else
            break;
    }
    return choice;
}


void MainMenu::run()
{
    int choice = 0;
    do
    {
        showMainMenu();
        choice = getUserInput();
        handleMainMenuChoice(choice);
    } while (choice != 3);
}


void MainMenu::showMainMenu()
{
    cout << " ===============================================================\n";
    cout << "    _____  _____  ____   _____    _____  _____  __     __ \n";    
    cout << "   |  |  ||   __||    \ |  _  |  |     ||  _  ||  |   |  | \n";   
    cout << "   |  |  ||   __||  |  ||     |  | | | ||     ||  |__ |  |__\n"; 
    cout << "    \___/ |_____||____/ |__|__|  |_|_|_||__|__||_____||_____|\n";

    cout << " ===============================================================\n";
    cout << "                    Welcome to VEDA Mall \n";
    cout << " ===============================================================\n";
    cout << "                       # 1. Customer #                          \n";
    cout << "                       # 2. Manager  #                          \n";
    cout << "                       # 3. Exit     #                          \n";
    cout << " ===============================================================\n";
    cout << "                  Enter your choice (0 ~ 3) >> ";

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
    cout << "<< Login Customer >> " << endl;
    cout << "Enter your phone number to login >> ";
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
        // cout << "\033[2J\033[1;1H";
        // cout << "\033[2J\033[1;1H";
        cout << "=====================|Customer Menu|========================\n";
        cout << "                      1. View Items                         \n";
        cout << "                      2. Purchase Items                     \n";
        cout << "                      3. View Points                        \n";
        cout << "                      4. Logout                             \n";
        cout << "=====================|Customer Menu|========================\n";
        cout << "                 Enter your choice (0 ~ 4) >> ";
        choice = getUserInput();

        handleCustomerMenuChoice(choice);
    } while (choice != 4);
}

void MainMenu::handleCustomerMenuChoice(int choice)
{
    switch (choice)
    {
    case 1:
        ItemManager.getAllItem();
        break;
    case 2:
    {
        if (!currentCustomer)
        {
            cout << "No customer is logged in. Please log in first." << endl;
            break;
        }

        string barcode;
        cout << "<< Purchase Items >>" << endl;
        cout << "Enter item barcode to purchase >> ";
        cin >> barcode;

        customerManager.purchaseItem(currentCustomer->getCustomerPhoneNumber(), barcode, ItemManager);

        cout << "Purchase successful. Points updated." << endl;
        break;
    }
    case 3:
        if (currentCustomer)
        {
            cout << "|Your current points| " << currentCustomer->getCustomerPoint() << endl;
        }
        else
        {
            cout << "No customer is logged in." << endl;
        }
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
        cout << "=====================|Manager Menu|========================\n";
        cout << "                      1. Customer Management               \n";
        cout << "                      2. Item Management                   \n";
        cout << "                      3. Back to Main Menu                 \n";
        cout << "=====================|Manager Menu|========================\n";
        cout << "                    Enter your choice (1 ~ 3) >> ";
        choice = getUserInput();

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
        cout << "=================|Customer Manager Menu|===================\n";
        cout << "                  1. Insert Customer                       \n";
        cout << "                  2. Search Customer                       \n";
        cout << "                  3. Update Customer                       \n";
        cout << "                  4. Delete Customer                       \n";
        cout << "                  5. Import Customer from CSV              \n";
        cout << "                  6. Export Customer from CSV              \n";
        cout << "                  7. Back to Manager Menu                  \n";
        cout << "=================|Customer Manager Menu|===================\n";
        cout << "                 Enter your choice (1 ~ 5) >> ";
        choice = getUserInput();

        handleCustomerManagementMenuChoice(choice);
    } while (choice != 7); 
}

void MainMenu::handleCustomerManagementMenuChoice(int choice)
{
    switch (choice)
    {
    case 1:
    { 
        string name, phone;

        cout << "<< Insert Customer >> " << endl;
        cout << "Insert NAME, PHONE NUMBER >> ";
        cin >> name >> phone;

        customerManager.insertCustomer(name, phone);
        cout << "Successfully added customer information" << endl;
        break;
    }
    case 2:
    { 
        string phone;
        cout << "<< Search Customer >> " << endl;
        cout << "Enter customer phone number to search >> ";
        cin >> phone;

        unique_ptr<Customer> &customer = customerManager.searchCustomer(phone);

        if (customer)
        {
            cout << " |Customer Found| " << endl;
            // cout << "ID: " << customer->getCustomerId() << endl;
            cout << "|Name | " << customer->getCustomerName() << endl;
            cout << "|Phone| " << customer->getCustomerPhoneNumber() << endl;
            cout << "|Point| " << customer->getCustomerPoint() << endl;
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
        cout << "<< Update Customer >>" << endl;
        cout << "Enter customer phone number to modify >> ";
        cin >> phone;

        unique_ptr<Customer> &customer = customerManager.searchCustomer(phone);

        unsigned int point;

        string name, n_phone;

        cout << "Insert new NAME, PHONE NUMBER, POINT >> ";
        cin >> name >> n_phone >> point;

        if (customer)
        {
            cout << "Customer Update Successful" << endl;
            customerManager.updateCustomer(phone, name, n_phone, point);
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
        cout << "<< Delete Customer  >>" << endl;
        cout << "Enter customer phone number to delete >> ";
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
    {
        char load_ans;
        cout<< "Warning : Your current customer data will be lost. Do you agree? [Y/n]  >> ";
        cin>>load_ans;
        if(load_ans=='Y'||load_ans=='y')
        {
            cout<< "Importing Customer List from CSV file to database " << endl;
            customerManager.loadFromCSV("customerList.csv");
            break;
        }
        else
        {
            cout<<"CSV Import aborted"<< endl;
            break;
        }
	break;
    }
    case 6:
    {
        cout << "Exporting Customer List from database to CSV file " << endl;
        customerManager.saveToCSV("customerList.csv");
        break;
    }
    case 7:
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
        cout << "==================|Item Management Menu|===================\n";
        cout << "                    1. Add Item                            \n";
        cout << "                    2. Get Item                            \n";
        cout << "                    3. Update Item                         \n";
        cout << "                    4. Delete Item                         \n";
        cout << "                    5. Import Items from CSV               \n";
        cout << "                    6. Export Items to CSV                 \n";
        cout << "                    7. Back to Main Menu                   \n";
        cout << "==================|Item Management Menu|===================\n";
        cout << "               Enter your choice (1 ~ 5) >> ";
        choice = getUserInput();

        handleItemManagementMenu(choice);
    } while (choice != 7);
}

void MainMenu::handleItemManagementMenu(int choice)
{
    string barcode, manufacturer;
    unsigned int price;
    Item *item;
    switch (choice)
    {
    case 1:
        cout << "<< Add Item >>" << endl;
        cout << "Type barcode, manufacturer, price >> ";
        cin >> barcode >> manufacturer >> price;
        if (ItemManager.addItem(barcode, manufacturer, price))
        {
            cout << "|Added Barcode| " << barcode << endl;
        }
        else
        {
            cout << "Item not found. Returning to Item Menu..." << endl;
            showItemManagementMenu();
        }
        break;
    case 2:
        cout << "<< Get Item >>" << endl;
        ItemManager.getAllItem();
        break;
    case 3:
        cout << "<< Update Item >>" << endl;
        cin >> barcode >> manufacturer >> price;
        if (ItemManager.updateItem(barcode, manufacturer, price))
        {
            cout << "|Updated Barcode| " << barcode;
        }
        else
        {
            cout << "Item not found. Returning to Item Menu..." << endl;
            showItemManagementMenu();
        }
        break;
    case 4:
        cout << "<< Delete Item >>" << endl;
        cout << "Type barcode >> ";
        cin >> barcode;
        if (ItemManager.deleteItem(barcode))
        {
            cout << "|Deleted Barcode| " << barcode;
        }
        else
        {
            cout << "Item not found. Returning to Item Menu..." << endl;
            showItemManagementMenu();
        }
        break;
    case 5:
    {
        char load_ans;
        cout << "Warning : Your current customer data will be lost. Do you agree? [Y/n]  >> ";
        cin >> load_ans;
        if (load_ans == 'Y' || load_ans == 'y')
        {
            cout << "Importing Customer List from CSV file to database " << endl;
            ItemManager.loadFromCSV("itemList.csv");
            break;
        }
        else
        {
            cout << "CSV Import aborted" << endl;
            break;
        }
        break;
    }
    case 6:
    {
        cout << "Exporting Item List from database to CSV file " << endl;
        ItemManager.saveToCSV("itemList.csv");
        break;
    }
    case 7:
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}