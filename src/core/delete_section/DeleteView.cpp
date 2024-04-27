#include "delete_section/DeleteView.h"
#include "utils/ConsoleUtils.h"
#include "models/Event.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

void DeleteView::display()
{
    ConsoleUtils::clearScreen();
    cout << "Delete an Event" << endl;
}

void DeleteView::displayEvents(const vector<Event *> &events)
{
    int index = 0;
    for (const auto &event : events)
    {
        cout << index++ << ". " << event->getTitle() << setw(15) << right << event->getDescription() << endl;
    }
}

void DeleteView::displayMenuOptions()
{
    ConsoleUtils::clearScreen();
    cout << "Are you sure you want to delete this event?" << endl;
    cout << "Title: " << selectedEvent->getTitle() << endl;
    cout << "Description: " << selectedEvent->getDescription() << endl;
    cout << "Date: " << selectedEvent->getDate() << endl;
    cout << "Time: " << selectedEvent->getTime() << endl;
    cout << "Yes or No (y/n):";
}

void DeleteView::setSelectedEvent(Event *event)
{
    selectedEvent = event;
}