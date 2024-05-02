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
}

void DeleteView::displayEventFields(const Event &event)
{
    cout << "Title: " << event.getTitle() << endl;
    cout << "Description: " << event.getDescription() << endl;
    cout << "Date: " << event.getDate() << endl;
    cout << "Time: " << event.getTime() << endl;
    cout << "Yes or No (y/n):";
}