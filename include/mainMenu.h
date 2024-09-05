#ifndef MAINMENU_H
#define MAINMENU_H

#include "customerManager.h" 
#include "itemManager.h"

class MainMenu {
public:
    void run();

private:
    void showMainMenu();
    void showCustomerMenu();
    void showManagerMenu();
    void showItemManagementMenu(); 
    void showCustomerManagementMenu(); 
    bool loginCustomer(); 

    void handleMainMenuChoice(int choice);
    void handleCustomerMenuChoice(int choice);
    void handleManagerMenuChoice(int choice);
    void handleCustomerManagementMenuChoice(int choice);
    void handleItemManagementMenu(int choice);

    int getUserInput();

    CustomerManager customerManager; 
    Customer* currentCustomer = nullptr; 
    ItemManager ItemManager;
};

#endif // MAINMENU_H