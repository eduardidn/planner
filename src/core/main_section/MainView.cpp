#include "main_section/MainView.h"
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

void MainView::display()
{
    system(CLEAR);
    vector<Event> eventMain = {
        Event("Event 1", "Description 1", "2021-10-10", "10:00", "daily", "high"),
        Event("Event 2", "Description 2", "2021-10-11", "11:00", "weekly", "medium")};
    cout << "Here are your events:" << endl;

    this->displayTable(eventMain);
    displayMenuOptions();
}

void MainView::displayWeeklyView()
{
    system(CLEAR);
    vector<Event>
        weeklyEventMain = {
            Event("Event 1", "Description 1", "2021-10-10", "10:00", "daily", "high"),
            Event("Event 2", "Description 2", "2021-10-11", "11:00", "weekly", "medium"),
            Event("Event 3", "Description 3", "2021-10-11", "11:00", "weekly", "medium"),
            Event("Event 4", "Description 4", "2021-10-11", "11:00", "weekly", "medium")};

    cout << "Here are your events for the week:" << endl;

    this->displayTable(weeklyEventMain);
    displayMenuOptions();
}

void MainView::displayMenuOptions()
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
    ConsoleUtils::displayOption("d", "Delete record", "Prompts the user to select records to delete from the available main.");
    ConsoleUtils::displayOption("q", "Exit", "Exit the application.");
}

/* --------------------------------- Helpers -------------------------------- */
void MainView::displayTable(vector<Event> eventMain)
{
    cout << endl;
    cout << left << setw(10) << "Event" << setw(20) << "Description"
         << setw(15) << "Date" << setw(10) << "Time" << setw(10)
         << "Recurring" << setw(10) << "Priority" << endl;
    cout << string(75, '-') << endl;

    for (const Event &event : eventMain)
    {
        cout << left << setw(10) << event.getName()
             << setw(20) << event.getDescription()
             << setw(15) << event.getDate()
             << setw(10) << event.getTime()
             << setw(10) << event.getRecurring()
             << setw(10) << event.getPriority() << endl;
    }
}