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
            cout << "\033[1;31mInvalid input. Please enter a number.\033[0m" << endl;
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
    cout << "   |  |  ||   __||   \\ |  _  |  |     ||  _  ||  |   |  | \n";   
    cout << "   |  |  ||   __||  |  ||     |  | | | ||     ||  |__ |  |__\n"; 
    cout << "   \\___/ |_____||____/ |__|__|  |_|_|_||__|__||_____||_____|\n";

    cout << " ===============================================================\n";
    cout << "                    Welcome to VEDA Mall \n";
    cout << " ===============================================================\n";
    cout << "                       # 1. Customer #                          \n";
    cout << "                       # 2. Manager  #                          \n";
    cout << "                       # 3. Exit     #                          \n";
    cout << " ===============================================================\n";
    cout << "\033[34m                 Enter your choice (1 ~ 3) >> \033[0m";

}

void MainMenu::handleMainMenuChoice(int choice)
{
    switch (choice)
    {
    case 1:
        if (loginCustomer())
        {
            cout << "\033[2J\033[1;1H";
            showCustomerMenu();
        }
        break;
    case 2:
        cout << "\033[2J\033[1;1H";
        showManagerMenu();
        break;
    case 3:
        cout << "\n\nExiting..." << endl;
        cout << "\033[2J\033[1;1H";
        return;
    default:
        cout << "\033[1;31mInvalid choice. Please try again.\033[0m" << endl;
        break;
    }
}

bool MainMenu::loginCustomer()
{
    string phone;
    cout << "\n\n\033[1;32m<< Login Customer >>\033[0m" << endl;
    cout << "\nEnter your phone number to login >> ";
    cin >> phone;

    unique_ptr<Customer> &customer = customerManager.searchCustomer(phone);

    if (customer)
    {
        cout << "\nLogin successful. Welcome, " << customer->getCustomerName() << "!" << endl;
        currentCustomer = customer.get();
        cout << "Press the Enter key ...";
        cin.get();  
        return true;
    }
    else
    {
        cout << "\n\033[1;31mLogin failed. Customer not found.\033[0m" << endl;
        cout << "Press the Enter key ..." << endl;
        cin.get();  
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
        cout << "\033[34m                 Enter your choice (1 ~ 4) >> \033[0m";
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
        cout << "Press the Enter key ...";
        cin.ignore();
        cin.get(); 
        cout << "\033[2J\033[1;1H";
        break;
    case 2:
    {
        if (!currentCustomer)
        {
            cout << "\nNo customer is logged in. Please log in first." << endl;
            cout << "Press the Enter key ...";
            cin.ignore();
            cin.get();
            cout << "\033[2J\033[1;1H";   
            break;
        }

        string barcode;
        cout << "\n\n\033[1;32m<< Purchase Item >>\033[0m" << endl;
        cout << "\nEnter item barcode to purchase >> ";
        cin >> barcode;

        customerManager.purchaseItem(currentCustomer->getCustomerPhoneNumber(), barcode, ItemManager);

        cout << "\nPurchase successful. Points updated." << endl;
        cout << "Press the Enter key ...";
        cin.ignore();
        cin.get();  
        cout << "\033[2J\033[1;1H";
        break;
    }
    case 3:
        if (currentCustomer)
        {
            cout << "\n|Your current points| " << currentCustomer->getCustomerPoint() << endl;
            cout << "Press the Enter key ...";
            cin.ignore();
            cin.get();  
            cout << "\033[2J\033[1;1H";
        }
        else
        {
            cout << "\nNo customer is logged in." << endl;
            cout << "Press the Enter key ...";
            cin.ignore();
            cin.get(); 
            cout << "\033[2J\033[1;1H";
        }
        break;
    case 4:
        cout << "\nLogging out..." << endl;
        currentCustomer = nullptr;
        cout << "\033[2J\033[1;1H";
    default:
        cout << "\033[1;31mInvalid choice. Please try again.\033[0m" << endl;
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
       cout << "\033[34m                 Enter your choice (1 ~ 3) >> \033[0m";
        choice = getUserInput();

        handleManagerMenuChoice(choice);
    } while (choice != 3);
}

void MainMenu::handleManagerMenuChoice(int choice)
{
    switch (choice)
    {
    case 1:
        cout << "\033[2J\033[1;1H"; 
        showCustomerManagementMenu();
        break;
    case 2:
        cout << "\033[2J\033[1;1H";
        showItemManagementMenu();
        break;
    case 3:
        cout << "\nReturning to Main Menu..." << endl;
        cout << "\033[2J\033[1;1H";
        break;
    default:
        cout << "\033[1;31mInvalid choice. Please try again.\033[0m" << endl;
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
        cout << "\033[34m                 Enter your choice (1 ~ 7) >> \033[0m";
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

        cout << "\n\n\033[1;32m<< Insert Customer >>\033[0m" << endl;
        cout << "\nInsert NAME, PHONE NUMBER >> ";
        cin >> name >> phone;

        customerManager.insertCustomer(name, phone);
        cout << "\nSuccessfully added customer information\n" << endl;
        cout << "Press the Enter key ...";
        cin.ignore(); 
        cin.get(); 
        cout << "\033[2J\033[1;1H";   
        break;
    }
    case 2:
    { 
        string phone;
        cout << "\n\n\033[1;32m<< Search Customer >>\033[0m" << endl;
        cout << "\nEnter customer phone number to search >> ";
        cin >> phone;

        unique_ptr<Customer> &customer = customerManager.searchCustomer(phone);

        if (customer)
        {
            cout << "\n |Customer Found| \n" << endl;
            // cout << "ID: " << customer->getCustomerId() << endl;
            cout << "|Name | " << customer->getCustomerName() << endl;
            cout << "|Phone| " << customer->getCustomerPhoneNumber() << endl;
            cout << "|Point| " << customer->getCustomerPoint() << endl;
        }
        else
        {
            cout << "\nCustomer not found ...\n" << endl;
        }
        cout << "Press the Enter key ...";
        cin.ignore();
        cin.get(); 
        cout << "\033[2J\033[1;1H";   
        break;
    }
    case 3:
    {
        string phone;
        cout << "\n\n\033[1;32m<< Update Customer >>\033[0m" << endl;
        cout << "\nEnter customer phone number to modify >> ";
        cin >> phone;

        unique_ptr<Customer> &customer = customerManager.searchCustomer(phone);

        unsigned int point;

        string name, n_phone;

        cout << "\nInsert new NAME, PHONE NUMBER, POINT >> ";
        cin >> name >> n_phone >> point;

        if (customer)
        {
            cout << "\nCustomer Update Successful\n" << endl;
            customerManager.updateCustomer(phone, name, n_phone, point);
        }
        else
        {
            cout << "\nCustomer not found ..." << endl;
        }
        cout << "Press the Enter key ...";
        cin.ignore();
        cin.get(); 
        cout << "\033[2J\033[1;1H";   
        break;
    }
    case 4:
    {
        string phone;
        cout << "\n\n\033[1;32m<< Delete Customer >>\033[0m" << endl;
        cout << "\nEnter customer phone number to delete >> ";
        cin >> phone;

        unique_ptr<Customer> &customer = customerManager.searchCustomer(phone);

        if (customer)
        {
            cout << "\nCustomer Successfully deleted" << endl;

            customerManager.deleteCustomer(phone);
        }
        else
        {
            cout << "\nCustomer not found ..." << endl;
        }
        cout << "Press the Enter key ...";
        cin.ignore();
        cin.get(); 
        cout << "\033[2J\033[1;1H";   
        break;
    }
    case 5:
    {
        char load_ans;
        cout<< "\nWarning : Your current customer data will be lost. Do you agree? [Y/n]  >> ";
        cin>>load_ans;
        if(load_ans=='Y'||load_ans=='y')
        {
            cout<< "\nImporting Customer List from CSV file to database " << endl;
            customerManager.loadFromCSV("customerList.csv");
            cout << "Press the Enter key ...";
            cin.ignore();
            cin.get(); 
            cout << "\033[2J\033[1;1H";   
            break;
        }
        else
        {
            cout<<"\nCSV Import aborted"<< endl;
            cout << "Press the Enter key ...";
            cin.ignore();
            cin.get(); 
            cout << "\033[2J\033[1;1H";   
            break;
        }
	    break;
    }
    case 6:
    {
        cout << "\nExporting Customer List from database to CSV file " << endl;
        customerManager.saveToCSV("customerList.csv");
        cout << "Press the Enter key ...";
        cin.ignore();
        cin.get(); 
        cout << "\033[2J\033[1;1H";   
        break;
    }
    case 7:
        cout << "\nReturning to Manager Menu..." << endl;
        cout << "\033[2J\033[1;1H";
        break;
    default:
        cout << "\033[1;31mInvalid choice. Please try again.\033[0m" << endl;
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
        cout << "\033[34m                 Enter your choice (0 ~ 7) >> \033[0m";
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
        cout << "\n\n\033[1;32m<< Add Item >>\033[0m" << endl;
        cout << "\nType barcode, manufacturer, price >> ";
        cin >> barcode >> manufacturer >> price;
        if (ItemManager.addItem(barcode, manufacturer, price))
        {
            cout << "\n|Added Barcode| " << barcode << endl;
        }
        else
        {
            cout << "\nItem not found. Returning to Item Menu..." << endl;
            cout << "Press the Enter key ...";
            cin.ignore();
            cin.get(); 
            showItemManagementMenu();
        }
        cout << "Press the Enter key ...";
        cin.ignore();
        cin.get(); 
        cout << "\033[2J\033[1;1H";   
        break;
    case 2:
        cout << "\n\n\033[1;32m<< Get Item >>\033[0m" << endl;
        ItemManager.getAllItem();
        cout << "Press the Enter key ...";
        cin.ignore();
        cin.get(); 
        cout << "\033[2J\033[1;1H";   
        break;
    case 3:
        cout << "\n\n\033[1;32m<< Update Item >>\033[0m" << endl;
        cin >> barcode >> manufacturer >> price;
        if (ItemManager.updateItem(barcode, manufacturer, price))
        {
            cout << "\n|Updated Barcode| " << barcode;
        }
        else
        {
            cout << "\nItem not found. Returning to Item Menu..." << endl;
            showItemManagementMenu();
        }
        cout << "Press the Enter key ...";
        cin.ignore();
        cin.get(); 
        cout << "\033[2J\033[1;1H";   
        break;
    case 4:
        cout << "\n\n\033[1;32m<< Delete Item >>\033[0m" << endl;
        cout << "\nType barcode >> ";
        cin >> barcode;
        if (ItemManager.deleteItem(barcode))
        {
            cout << "\n|Deleted Barcode| " << barcode;
        }
        else
        {
            cout << "\nItem not found. Returning to Item Menu..." << endl;
            showItemManagementMenu();
        }
        cout << "Press the Enter key ...";
        cin.ignore();
        cin.get(); 
        cout << "\033[2J\033[1;1H";   
        break;
    case 5:
    {
        char load_ans;
        cout << "\nWarning : Your current customer data will be lost. Do you agree? [Y/n]  >> ";
        cin >> load_ans;
        if (load_ans == 'Y' || load_ans == 'y')
        {
            cout << "\nImporting Customer List from CSV file to database " << endl;
            ItemManager.loadFromCSV("itemList.csv");
            cout << "Press the Enter key ...";
            cin.ignore();
            cin.get(); 
            cout << "\033[2J\033[1;1H";   
            break;
        }
        else
        {
            cout << "\nCSV Import aborted" << endl;
            cout << "Press the Enter key ...";
            cin.ignore();
            cin.get(); 
            cout << "\033[2J\033[1;1H";   
            break;
        }
        break;
    }
    case 6:
    {
        cout << "\nExporting Item List from database to CSV file " << endl;
        ItemManager.saveToCSV("itemList.csv");
        cout << "Press the Enter key ...";
        cin.ignore();
        cin.get(); 
        cout << "\033[2J\033[1;1H";   
        break;
    }
    case 7:
        cout << "\nReturning to Manager Menu..." << endl;
        cout << "\033[2J\033[1;1H";
        break;
    default:
        cout << "\033[1;31mInvalid choice. Please try again.\033[0m" << endl;
        break;
    }
}