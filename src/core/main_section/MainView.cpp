#include "main_section/MainView.h"
#include "utils/ConsoleUtils.h"
#include "utils/DateUtils.h"
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

MainView::MainView() {}

void MainView::display()
{
    ConsoleUtils::clearScreen();
    string currentDate = DateUtils::getCurrentDate();
    cout << "Here are the events for today " << currentDate << endl;
    if (dailyEvents.size() == 0)
    {
        cout << endl;
        cout << "No events found." << endl;
    }
    else
    {
        this->displayTable(dailyEvents);
    }
    displayMenuOptions();
}

void MainView::displayWeeklyView()
{
    ConsoleUtils::clearScreen();

    cout << "Here are your events for the week:" << endl;
    if (weeklyEventMain.size() == 0)
    {
        cout << endl;
        cout << "No events found." << endl;
    }
    else
    {
        this->displayTable(weeklyEventMain);
    }
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
    ConsoleUtils::displayOption("e", "Edit record", "Moves to the edit record screen to modify existing events.");
    ConsoleUtils::displayOption("a", "Add record", "Displays options on how the user can create a new record.");
    ConsoleUtils::displayOption("d", "Delete record", "Prompts the user to select records to delete from the available main.");
    ConsoleUtils::displayOption("q", "Exit", "Exit the application.");
}

/* --------------------------------- Helpers -------------------------------- */
void MainView::displayTable(const vector<Event *> &events)
{
    cout << endl;
    cout << left << setw(10) << "Event" << setw(20) << "Description"
         << setw(15) << "Date" << setw(10) << "Time" << setw(10)
         << "Recurring" << setw(10) << "Priority" << endl;
    cout << string(75, '-') << endl;

    for (const auto &event : events)
    {

        cout << left << setw(10) << event->getTitle()
             << setw(20) << truncate(event->getTitle(), 20)
             << setw(30) << truncate(event->getDescription(), 30)
             << setw(10) << event->getTime()
             << setw(10) << event->getFrequency()
             << setw(10) << event->getPriority() << endl;
    }
}

string MainView::truncate(const string &str, int width)
{
    if (str.length() > width)
    {
        return str.substr(0, width - 3) + "...";
    }
    return str;
}

/* --------------------------------- Getters -------------------------------- */
vector<Event *> MainView::getDailyEvents()
{
    return dailyEvents;
}

vector<Event *> MainView::getWeeklyEvents()
{
    return weeklyEventMain;
}

/* --------------------------------- Setters -------------------------------- */

void MainView::setDailyEvents(vector<Event *> events)
{
    dailyEvents = events;
}

void MainView::setWeeklyEvents(vector<Event *> events)
{
    weeklyEventMain = events;
}