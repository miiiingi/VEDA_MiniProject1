#include "mainMenu.h"
#include "customer.h"  

#include <iostream>

using namespace std;

void MainMenu::run() {
    int choice = 0;
    do {
        showMainMenu();
        cin >> choice;
        handleMainMenuChoice(choice);
    } while (choice != 4);  
}

void MainMenu::showMainMenu() {
    cout << "\n=== Welcome to VEDA mall ===" << endl;
    cout << "1. Customer" << endl;
    cout << "2. Item" << endl;
    cout << "3. T.B.D" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice >> ";
}

void MainMenu::handleMainMenuChoice(int choice) {
    switch (choice) {
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

void MainMenu::showCustomerMenu() {
    int choice = 0;
    do {
        cout << "\n=== Customer Menu ===" << endl;
        cout << "1. Insert Customer" << endl;
        cout << "2. Search Customer" << endl;
        cout << "3. Modify Customer (T.B.D)" << endl;
        cout << "4. Delete Customer (T.B.D)" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice >> ";
        cin >> choice;
        handleCustomerMenuChoice(choice);
    } while (choice != 5);
}

void MainMenu::handleCustomerMenuChoice(int choice) {
    switch (choice) {
    case 1: {       // 1. Insert Costomer
        unsigned int id;
        string name, phone;

        cout << "Insert ID, NAME, PHONE NUMBER >> " << endl;
        cin >> id >> name >> phone;

        customerManager.insertCustomer(id, name, phone);
        cout << "Successfully added customer information" << endl;
        break;
    }
    case 2:  {      // 2. Search Customer
        string phone;
        cout << "Enter customer phone number to search >> " << endl;
        cin >> phone;

        unique_ptr<Customer>& customer = customerManager.searchCustomer(phone);

        if (customer) {
            cout << "Customer Found" << endl;
            cout << "ID: " << customer->getCustomerId() << endl;
            cout << "Name: " << customer->getCustomerName() << endl;
            cout << "Phone: " << customer->getCustomerPhoneNumber() << endl;
        }
        else {
            cout << "Customer not found ..." << endl;
        }
        break;
    }
    case 3:
        cout << "Modify Customer (T.B.D)..." << endl; 
        break;
    case 4:
        cout << "Delete Customer (T.B.D)..." << endl; 
        break;
    case 5:
        break; 
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}

void MainMenu::showItemMenu() {
    int choice = 0;
    do {
        cout << "\n=== Item Menu ===" << endl;
        cout << "1. View Item list" << endl;
        cout << "2. T.B.D" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice >> ";
        cin >> choice;
        handleItemMenuChoice(choice);
    } while (choice != 3);  
}

void MainMenu::handleItemMenuChoice(int choice) {
    switch (choice) {
    case 1:
        cout << "View Item list..." << endl; 
        break;
    case 2:
        cout << "to be determined..." << endl; 
        break;
    case 3:
        break;
    }
}