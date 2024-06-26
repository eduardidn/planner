#include "delete_section/DeleteController.h"
#include "utils/ConsoleUtils.h"
#include "utils/EventUtils.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>
using namespace std;

DeleteController::DeleteController(function<void()> mainViewCallback) : onShowMainViewCallback(mainViewCallback) {}

void DeleteController::handleDisplay()
{
    deleteView.display();
    if (eventToDelete.has_value())
    {
        deleteView.displayMenuOptions();
        deleteView.displayEventFields(eventToDelete.value());
        whileUserMenuSelection();
    }
    else
    {
        deleteView.displayEvents(events);
        selectEventHearing();
    }
}

void DeleteController::whileUserMenuSelection()
{
    isMenuHearing = true;
    char command = '\0';
    while (isMenuHearing)
    {
        cin >> command;
        switch (command)
        {
        case 'y':
            deleteEvent();
            break;
        case 'n':
            goBackToList();
            break;
        default:
            cout << "Invalid input, please enter a a valid command (y/n):";
            break;
        }
    }
}

void DeleteController::selectEventHearing()
{
    isMenuHearing = true;
    char command = '\0';
    while (isMenuHearing)
    {
        cout << "Please select an event from the list to delete or 'q' to quit: ";
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
            setEventToDeleteFromIndex(selection);
        }
        else
        {
            cout << "Invalid input, please enter a event number or 'q' to quit." << endl;
        }
    }
}

void DeleteController::setEventToDeleteFromIndex(const int &index)
{
    Event selectedEvent = *events[index];
    setEventToDelete(selectedEvent);
}

void DeleteController::setEventToDelete(const Event &event)
{
    isMenuHearing = false;
    eventToDelete.emplace(event);
    handleDisplay();
}

/* --------------------------------- Helpers -------------------------------- */
void DeleteController::deleteEvent()
{
    try
    {
        eventToDelete->deleteEvent();
        onDeleteEventCallback();
        redirectToMainView();
    }
    catch (const pqxx::sql_error &e)
    {
        cerr << "Something went wrong, please try again ";
    }
    catch (const exception &e)
    {
        cerr << "Something went wrong, please try again " << e.what() << endl;
    }
}

void DeleteController::goBackToList()
{
    resetState();
    handleDisplay();
}

void DeleteController::redirectToMainView()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    resetState();
    onShowMainViewCallback();
}

void DeleteController::resetState()
{
    eventToDelete.reset();
    isMenuHearing = false;
}

/* --------------------------------- Setters -------------------------------- */
void DeleteController::setEvents(const vector<Event *> &events)
{
    this->events = events;
}

void DeleteController::setOnDeleteEventCallback(function<void()> cb)
{
    onDeleteEventCallback = cb;
}