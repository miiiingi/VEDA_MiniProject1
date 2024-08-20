#ifndef MAINMENU_H
#define MAINMENU_H

#include "customerManager.h"  // CustomerManager

class MainMenu {
public:
    void run();

private:
    void showMainMenu();
    void handleMainMenuChoice(int choice);
    void showCustomerMenu();
    void showItemMenu();
    void handleCustomerMenuChoice(int choice);
    void handleItemMenuChoice(int choice);

    CustomerManager customerManager; // Customer Manager
};

#endif // MAINMENU_H
