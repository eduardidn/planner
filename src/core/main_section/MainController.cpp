#include "main_section/MainController.h"

#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

MainController::MainController(std::function<void()> createViewCallback) : onCreateViewCallback(createViewCallback) {}

void MainController::handleDisplay()
{
    setSelectedView(ViewMode::Daily);
    mainView.display();
    if (!isMenuHearing)
    {
        whileUserMenuSelection();
    }
}

void MainController::handleDisplayWeeklyView()
{
    setSelectedView(ViewMode::Weekly);
    mainView.displayWeeklyView();
    if (!isMenuHearing)
    {
        whileUserMenuSelection();
    }
}

void MainController::whileUserMenuSelection()
{
    this->setIsMenuHearing(true);
    char command = '\0';

    while (command != 'q' && isMenuHearing)
    {
        cout << endl
             << "Enter command: ";
        std::cin >> command;

        switch (command)
        {
        case 'v':;
            switchViews();
            break;
        case 'f':
            cout << "Waiting for connection with the DB to do this";
            break;
        case 'e':
            cout << "Waiting for edit view";
            break;
        case 'a':
            onCreateViewCallback();
            break;
        case 'd':
            cout << "Waiting for delete option to be ready";
            break;
        case 'q':
            cout << "Quit";
            break;
        default:
            cout << "Invalid command, Please select a valid option from the main." << endl;
            break;
        }
    };
}

void MainController::switchViews()
{
    if (selectedView == ViewMode::Daily)
    {
        handleDisplayWeeklyView();
        return;
    }

    handleDisplay();
}

/* --------------------------------- Getters -------------------------------- */
bool MainController::getIsMenuHearing()
{
    return this->isMenuHearing;
}

/* --------------------------------- Setters -------------------------------- */
void MainController::setSelectedView(ViewMode value)
{
    this->selectedView = value;
}

void MainController::setIsMenuHearing(bool value)
{
    this->isMenuHearing = value;
}
