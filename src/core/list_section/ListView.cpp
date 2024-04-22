#include "list_section/ListView.h"
#include "utils/ConsoleUtils.h"
#include "models/Event.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void ListView::display()
{
    this->setSelectedView(ViewMode::Daily);
    system(CLEAR);
    vector<Event> eventList = {
        Event("Event 1", "Description 1", "2021-10-10", "10:00", "daily", "high"),
        Event("Event 2", "Description 2", "2021-10-11", "11:00", "weekly", "medium")};
    cout << "Here are your events:" << endl;

    this->displayTable(eventList);
    this->displayMenuOptions();
    if (!this->getIsMenuHearing())
    {
        this->whileUserMenuSelection();
    }
}

void ListView::displayWeeklyView()
{
    this->setSelectedView(ViewMode::Weekly);
    system(CLEAR);
    vector<Event>
        weeklyEventList = {
            Event("Event 1", "Description 1", "2021-10-10", "10:00", "daily", "high"),
            Event("Event 2", "Description 2", "2021-10-11", "11:00", "weekly", "medium"),
            Event("Event 3", "Description 3", "2021-10-11", "11:00", "weekly", "medium"),
            Event("Event 4", "Description 4", "2021-10-11", "11:00", "weekly", "medium")};

    cout << "Here are your events for the week:" << endl;

    this->displayTable(weeklyEventList);
    this->displayMenuOptions();
}

void ListView::displayMenuOptions()
{
    cout << endl;
    cout << left << setw(15) << "Command"
         << setw(30) << "Action"
         << setw(50) << "Description" << endl;
    cout << string(95, '-') << endl;

    ConsoleUtils::displayOption("v", "Toggle view (weekly/daily)", "Switches the display between weekly and daily views.");
    ConsoleUtils::displayOption("f", "Set view as favorite", "Marks the selected view as a favorite, highlighting it.");
    ConsoleUtils::displayOption("e", "Edit record", "Moves to the edit record screen to modify existing events.");
    ConsoleUtils::displayOption("a", "Add record", "Displays options on how the user can create a new record.");
    ConsoleUtils::displayOption("d", "Delete record", "Prompts the user to select records to delete from the available list.");
    ConsoleUtils::displayOption("q", "Exit", "Exit the application.");
}

void ListView::whileUserMenuSelection()
{
    this->setIsMenuHearing(true);
    char command = '\0';
    do
    {
        cout << endl
             << "Enter command: ";
        cin >> command;

        switch (command)
        {
        case 'v':
            this->switchViews();
            break;
        case 'f':
            cout << "Waiting for connection with the DB to do this";
            break;
        case 'e':
            cout << "Waiting for edit view";
            break;
        case 'a':
            cout << "Waiting for creation view";
            break;
        case 'd':
            cout << "Waiting for delete option to be ready";
            break;
        case 'q':
            cout << "Quit" << endl;
            break;
        default:
            cout << "Invalid command, Please select a valid option from the list." << endl;
            break;
        }
    } while (command != 'q');
}

void ListView::switchViews()
{
    if (selectedView == ViewMode::Daily)
    {
        displayWeeklyView();
        return;
    }

    display();
}

/* --------------------------------- Getters -------------------------------- */
bool ListView::getIsMenuHearing()
{
    return this->isMenuHearing;
}

/* --------------------------------- Setters -------------------------------- */
void ListView::setSelectedView(ViewMode value)
{
    this->selectedView = value;
}

void ListView::setIsMenuHearing(bool value)
{
    this->isMenuHearing = value;
}

/* --------------------------------- Helpers -------------------------------- */
void ListView::displayTable(vector<Event> eventList)
{
    cout << endl;
    cout << left << setw(10) << "Event" << setw(20) << "Description"
         << setw(15) << "Date" << setw(10) << "Time" << setw(10)
         << "Recurring" << setw(10) << "Priority" << endl;
    cout << string(75, '-') << endl;

    for (const Event &event : eventList)
    {
        cout << left << setw(10) << event.getName()
             << setw(20) << event.getDescription()
             << setw(15) << event.getDate()
             << setw(10) << event.getTime()
             << setw(10) << event.getRecurring()
             << setw(10) << event.getPriority() << endl;
    }
}