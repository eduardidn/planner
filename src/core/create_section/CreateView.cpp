#include "create_section/CreateView.h"
#include "utils/ConsoleUtils.h"
#include "models/Event.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

void CreateView::display()
{
    ConsoleUtils::clearScreen();
    cout << "Lets create an Event" << endl;
}

void CreateView::displayEventFields(map<string, string> newEvent)
{
    cout << "These are the event fields:" << endl;
    cout << "1. Title: " << newEvent["title"] << endl;
    cout << "2. Description: " << newEvent["description"] << endl;
    cout << "3. Date: " << newEvent["date"] << endl;
    cout << "4. Time: " << newEvent["time"] << endl;
    cout << "5. Frequency: " << newEvent["frequency"] << endl;
    cout << "6. Priority: " << newEvent["priority"] << endl;
    cout << "Please enter the values for the fields" << endl;
}

void CreateView::displayMenuOptions()
{
    cout << endl;
    cout << left << setw(15) << "Command"
         << setw(30) << "Action"
         << setw(50) << "Description" << endl;
    cout << string(95, '-') << endl;

    ConsoleUtils::displayOption("1", "Title", "Enter the title of the event. (Required )");
    ConsoleUtils::displayOption("2", "Description", "Enter the description of the event.");
    ConsoleUtils::displayOption("3", "Date", "Enter the date of the event. (Required )");
    ConsoleUtils::displayOption("4", "Time", "Enter the time of the event. (Required )");
    ConsoleUtils::displayOption("5", "Frequency", "Enter the frequency of the event. (default: once)");
    ConsoleUtils::displayOption("6", "Priority", "Enter the priority of the event. (default: low)");
    ConsoleUtils::displayOption("s", "Save", "Save this event.");
    ConsoleUtils::displayOption("q", "Exit", "Go back to the main menu.");
}