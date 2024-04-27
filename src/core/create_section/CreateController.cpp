#include "create_section/CreateController.h"
#include "utils/ConsoleUtils.h"
#include "utils/EventUtils.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>
using namespace std;

CreateController::CreateController(function<void()> createViewCallback) : onShowMainViewCallback(createViewCallback) {}

void CreateController::handleDisplay()
{
    createView.display();
    createView.displayEventFields(newEventFields);
    createView.displayMenuOptions();
    if (!isMenuHearing)
    {
        whileUserMenuSelection();
    }
}

void CreateController::whileUserMenuSelection()
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
        case '1':
            setEventStringField("title", "Enter the title of the event");
            break;
        case '2':
            setEventStringField("description", "Enter the description of the event");
            break;
        case '3':
            setEventDateField();
            break;
        case '4':
            setEventTimeField();
            break;
        case '5':
            setEventFrequencyField();
            break;
        case '6':
            setEventPriorityField();
            break;
        case 's':
            saveEvent();
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
void CreateController::setEventStringField(const string &field, const string &value)
{
    ConsoleUtils::clearScreen();
    string fieldValue = ConsoleUtils::getEventStringField(field, value);
    newEventFields[field] = fieldValue;
    handleDisplay();
}

void CreateController::setEventDateField()
{
    ConsoleUtils::clearScreen();
    cout << "Enter the date of the event" << endl;
    string date = ConsoleUtils::getEventDateField();
    newEventFields["date"] = date;
    handleDisplay();
}

void CreateController::setEventTimeField()
{
    ConsoleUtils::clearScreen();
    cout << "Enter the time of the event" << endl;
    string time = ConsoleUtils::getEventTimeField();
    newEventFields["time"] = time;
    handleDisplay();
}

void CreateController::setEventFrequencyField()
{
    ConsoleUtils::clearScreen();
    cout << "Enter the frequency of the event" << endl;
    string frequency = ConsoleUtils::getEventFrequencyField();
    newEventFields["frequency"] = frequency;
    handleDisplay();
}

void CreateController::setEventPriorityField()
{
    ConsoleUtils::clearScreen();
    cout << "Enter the priority of the event" << endl;
    string priority = ConsoleUtils::getEventPriorityField();
    newEventFields["priority"] = priority;
    handleDisplay();
}

void CreateController::saveEvent()
{
    bool canSaveEvent = EventUtils::validateEvent(newEventFields);
    if (!canSaveEvent)
        return;

    Event newEvent(
        newEventFields["title"],
        newEventFields["description"],
        newEventFields["date"],
        newEventFields["time"],
        newEventFields["frequency"].empty() ? "once" : newEventFields["frequency"],
        newEventFields["priority"]);
    onCreateEventCallback(newEvent);
    redirectToMainView();
}

void CreateController::redirectToMainView()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    resetState();
    onShowMainViewCallback();
}

void CreateController::resetState()
{
    newEventFields = {};
    isMenuHearing = false;
}

/* --------------------------------- Getters -------------------------------- */
bool CreateController::getIsMenuHearing()
{
    return isMenuHearing;
}

/* --------------------------------- Setters -------------------------------- */
void CreateController::setIsMenuHearing(bool value)
{
    isMenuHearing = value;
}

void CreateController::setOnCreateEventCallback(function<void(Event)> cb)
{
    onCreateEventCallback = cb;
}