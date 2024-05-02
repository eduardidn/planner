#include "detail_section/DetailController.h"
#include "utils/ConsoleUtils.h"
#include "utils/EventUtils.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>
using namespace std;

DetailController::DetailController(function<void()> showMainViewCb, function<void(function<void()>, const Event &event)> editViewCb, function<void(function<void()>, const Event &event)> deleteViewCb)
    : onShowMainViewCallback(showMainViewCb),
      onEditViewCallback(editViewCb),
      onDeleteViewCallback(deleteViewCb) {}

void DetailController::handleDisplay()
{
    detailView.display();
    if (event.has_value())
    {
        detailView.displayEventFields(event.value());
    }

    detailView.displayMenuOptions();
    if (!isMenuHearing)
        whileUserMenuSelection();
}

void DetailController::whileUserMenuSelection()
{
    this->setIsMenuHearing(true);
    char command = '\0';
    while (command != 'q' && isMenuHearing)
    {
        cout << endl
             << "Enter command: ";
        cin >> command;

        switch (command)
        {
        case 'e':
            redirectToEditView();
            break;
        case 'd':
            redirectToDeleteView();
            break;
        default:
            cout << "Invalid command, Please select a valid option from the menu." << endl;
            break;
        }
    };

    if (command == 'q')
    {
        redirectToMainView();
    }
}

/* --------------------------------- Helpers -------------------------------- */
void DetailController::redirectToMainView()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    resetState();
    onShowMainViewCallback();
}

void DetailController::redirectToEditView()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto onEditCb = bind(&DetailController::onEditCallback, this);
    onEditViewCallback(onEditCb, event.value());
    resetState();
}

void DetailController::redirectToDeleteView()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto onDeleteCb = bind(&DetailController::onDeleteCallback, this);
    onDeleteViewCallback(onDeleteCb, event.value());
    resetState();
}

void DetailController::resetState()
{
    event.reset();
    isMenuHearing = false;
}

void DetailController::onEditCallback()
{
    onReloadCb();
}

void DetailController::onDeleteCallback()
{
    onReloadCb();
}

/* --------------------------------- Getters -------------------------------- */
bool DetailController::getIsMenuHearing()
{
    return isMenuHearing;
}

/* --------------------------------- Setters -------------------------------- */
void DetailController::setIsMenuHearing(bool value)
{
    isMenuHearing = value;
}

void DetailController::setEvent(const Event &newEvent)
{
    event.emplace(newEvent);
}

void DetailController::setOnReloadCallback(const function<void()> &cb)
{
    onReloadCb = cb;
}