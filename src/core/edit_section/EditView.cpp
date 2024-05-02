#include "edit_section/EditView.h"
#include "utils/ConsoleUtils.h"
#include "models/Event.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

void EditView::display()
{
    ConsoleUtils::clearScreen();
    cout << "Let's edit an Event" << endl;
}

void EditView::displayEvents(const vector<Event *> &events)
{
    int index = 0;
    for (const auto &event : events)
    {
        cout << index++ << ". " << event->getTitle() << setw(15) << right << event->getDescription() << endl;
    }
}

void EditView::displayEventFields(map<string, string> event)
{
    cout << "These are the event fields you can edit:" << endl;
    cout << "1. Title: " << event["title"] << endl;
    cout << "2. Description: " << event["description"] << endl;
    cout << "3. Date: " << event["date"] << endl;
    cout << "4. Time: " << event["time"] << endl;
    cout << "5. Frequency: " << event["frequency"] << endl;
    cout << "6. Priority: " << event["priority"] << endl;
    cout << "Please enter the values for the fields" << endl;
}

void EditView::displayMenuOptions()
{
    cout << endl;
    cout << left << setw(15) << "Command"
         << setw(30) << "Action"
         << setw(50) << "Description" << endl;
    cout << string(95, '-') << endl;

    ConsoleUtils::displayOption("1", "Title", "Enter the title of the event.");
    ConsoleUtils::displayOption("2", "Description", "Enter the description of the event.");
    ConsoleUtils::displayOption("3", "Date", "Enter the date of the event.");
    ConsoleUtils::displayOption("4", "Time", "Enter the time of the event.");
    ConsoleUtils::displayOption("5", "Frequency", "Enter the frequency of the event.");
    ConsoleUtils::displayOption("6", "Priority", "Enter the priority of the event.");
    ConsoleUtils::displayOption("s", "Save", "Save the changes and edit the event.");
    ConsoleUtils::displayOption("q", "Exit", "Go back to the main menu.");
}