#include "detail_section/DetailView.h"
#include "utils/ConsoleUtils.h"
#include "models/Event.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <map>

void DetailView::display()
{
    ConsoleUtils::clearScreen();
    cout << "These are the event's details" << endl;
}

void DetailView::displayEventFields(const Event &event)
{
    cout << "These are the event fields you can edit:" << endl;
    cout << "1. Title: " << event.getTitle() << endl;
    cout << "2. Description: " << event.getDescription() << endl;
    cout << "3. Date: " << event.getDate() << endl;
    cout << "4. Time: " << event.getTime() << endl;
    cout << "5. Frequency: " << event.getFrequency() << endl;
    cout << "6. Priority: " << event.getPriority() << endl;
    cout << "Please enter the values for the fields" << endl;
}

void DetailView::displayMenuOptions()
{
    cout << endl;
    cout << left << setw(15) << "Command"
         << setw(30) << "Action"
         << setw(50) << "Description" << endl;
    cout << string(95, '-') << endl;

    ConsoleUtils::displayOption("e", "Edit", "Edit the event.");
    ConsoleUtils::displayOption("d", "Delete", "Delete the event.");
    ConsoleUtils::displayOption("q", "Exit", "Go back to the main menu.");
}