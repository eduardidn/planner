#include "edit_section/EditController.h"
#include "utils/ConsoleUtils.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>
using namespace std;

EditController::EditController(function<void()> editViewCallback) : onShowMainViewCallback(editViewCallback) {}

void EditController::handleDisplay()
{
    editView.display();
    if (eventIndex == -1)
    {
        editView.displayEvents(events);
        if (!isMenuHearing)
            selectEventHearing();
    }
    else
    {
        editView.displayEventFields(EventToEditFields);
        editView.displayMenuOptions();
        if (!isMenuHearing)
            whileUserMenuSelection();
    }
}

void EditController::whileUserMenuSelection()
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
            setEventStringField("title", "Enter the new title of the event");
            break;
        case '2':
            setEventStringField("description", "Enter the new description of the event");
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
            editEvent();
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

void EditController::selectEventHearing()
{
    setIsMenuHearing(true);
    char command = '\0';
    while (isMenuHearing)
    {
        cout << "Please select an event from the list to edit: ";
        cin >> command;

        if (command == 'q')
        {
            redirectToMainView();
            return;
        }

        if (isdigit(command))
        {
            int selection = command - '0';
            if (selection < 0 || selection >= events.size())
            {
                cout << "Invalid selection!" << endl;
                continue;
            }
            setEventToEdit(selection);
        }
        else
        {
            cout << "Invalid input, please enter a event number or 'q' to quit." << endl;
        }
    }
}

void EditController::setEventToEdit(const int &index)
{
    Event &selectedEvent = *events[index];
    eventIndex = index;
    EventToEditFields = {
        {"title", selectedEvent.getTitle()},
        {"description", selectedEvent.getDescription()},
        {"date", selectedEvent.getDate()},
        {"time", selectedEvent.getTime()},
        {"frequency", selectedEvent.getFrequency()},
        {"priority", selectedEvent.getPriority()}};
    setIsMenuHearing(false);
    handleDisplay();
}

/* --------------------------------- Helpers -------------------------------- */
void EditController::setEventStringField(const string &field, const string &value)
{
    ConsoleUtils::clearScreen();
    string fieldValue = ConsoleUtils::getEventStringField(field, value);
    EventToEditFields[field] = fieldValue;
    handleDisplay();
}

void EditController::setEventDateField()
{
    ConsoleUtils::clearScreen();
    cout << "Enter the date of the event" << endl;
    string date = ConsoleUtils::getEventDateField();
    EventToEditFields["date"] = date;
    handleDisplay();
}

void EditController::setEventTimeField()
{
    ConsoleUtils::clearScreen();
    cout << "Enter the time of the event" << endl;
    string time = ConsoleUtils::getEventTimeField();
    EventToEditFields["time"] = time;
    handleDisplay();
}

void EditController::setEventFrequencyField()
{
    ConsoleUtils::clearScreen();
    cout << "Enter the frequency of the event" << endl;
    string frequency = ConsoleUtils::getEventFrequencyField();
    EventToEditFields["frequency"] = frequency;
    handleDisplay();
}

void EditController::setEventPriorityField()
{
    ConsoleUtils::clearScreen();
    cout << "Enter the priority of the event" << endl;
    string priority = ConsoleUtils::getEventPriorityField();
    EventToEditFields["priority"] = priority;
    handleDisplay();
}

void EditController::editEvent()
{
    events[eventIndex]->editEvent(EventToEditFields);
    redirectToMainView();
}

void EditController::redirectToMainView()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    resetState();
    onShowMainViewCallback();
}

void EditController::resetState()
{
    EventToEditFields = {};
    eventIndex = -1;
    isMenuHearing = false;
}

/* --------------------------------- Getters -------------------------------- */
bool EditController::getIsMenuHearing()
{
    return isMenuHearing;
}

/* --------------------------------- Setters -------------------------------- */
void EditController::setIsMenuHearing(bool value)
{
    isMenuHearing = value;
}

void EditController::setEvents(const vector<Event *> &events)
{
    this->events = events;
}