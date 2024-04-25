#include "create_section/CreateController.h"
#include "utils/ConsoleUtils.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>
using namespace std;

CreateController::CreateController(std::function<void()> createViewCallback) : onShowMainViewCallback(createViewCallback) {}

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
            // save
            break;
        default:
            cout << "Invalid command, Please select a valid option from the main." << endl;
            break;
        }
    };

    if (command == 'q')
    {
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        setIsMenuHearing(false);
        onShowMainViewCallback();
    }
}

/* --------------------------------- Helpers -------------------------------- */
void CreateController::setEventStringField(const string &field, const string &value)
{
    createView.clearView();
    string fieldValue = ConsoleUtils::getEventStringField(field, value);
    newEventFields[field] = fieldValue;
    handleDisplay();
}

void CreateController::setEventDateField()
{
    createView.clearView();
    cout << "Enter the date of the event" << endl;
    string date = ConsoleUtils::getEventDateField();
    newEventFields["date"] = date;
    handleDisplay();
}

void CreateController::setEventTimeField()
{
    createView.clearView();
    cout << "Enter the time of the event" << endl;
    string time = ConsoleUtils::getEventTimeField();
    newEventFields["time"] = time;
    handleDisplay();
}

void CreateController::setEventFrequencyField()
{
    createView.clearView();
    cout << "Enter the frequency of the event" << endl;
    string frequency = ConsoleUtils::getEventFrequencyField();
    newEventFields["frequency"] = frequency;
    handleDisplay();
}

void CreateController::setEventPriorityField()
{
    createView.clearView();
    cout << "Enter the priority of the event" << endl;
    string priority = ConsoleUtils::getEventPriorityField();
    newEventFields["priority"] = priority;
    handleDisplay();
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