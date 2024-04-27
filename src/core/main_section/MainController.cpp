#include "main_section/MainController.h"
#include "models/Event.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
using namespace std;

MainController::MainController(function<void(function<void(Event)>)> createViewCallback, function<void(const vector<Event *> &events)> editViewCb) : onCreateViewCallback(createViewCallback), onEditViewCallback(editViewCb) {}

void MainController::handleDisplay()
{
    setSelectedView(ViewMode::Daily);
    mainView.display();
    if (!isMenuHearing)
    {
        whileUserMenuSelection();
    }
}

void MainController::handleDisplayWeeklyView()
{
    setSelectedView(ViewMode::Weekly);
    mainView.displayWeeklyView();
    if (!isMenuHearing)
    {
        whileUserMenuSelection();
    }
}

void MainController::whileUserMenuSelection()
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
        case 'v':;
            switchViews();
            break;
        case 'f':
            cout << "Waiting for connection with the DB to do this";
            break;
        case 'e':
        {
            vector<Event *> events = selectedView == ViewMode::Daily ? mainView.getDailyEvents() : mainView.getWeeklyEvents();
            onEditViewCallback(events);
            break;
        }
        case 'a':
        {
            auto addEventCallback = bind(&MainController::addEvent, this, placeholders::_1);
            onCreateViewCallback(addEventCallback);
            break;
        }
        case 'd':
            cout << "Waiting for delete option to be ready";
            break;
        case 'q':
            cout << "Quit";
            break;
        default:
            cout << "Invalid command, Please select a valid option from the menu." << endl;
            break;
        }
    };
}

void MainController::switchViews()
{
    if (selectedView == ViewMode::Daily)
    {
        handleDisplayWeeklyView();
        return;
    }

    handleDisplay();
}

void MainController::addEvent(const Event &event)
{
    vector<Event *> currentEvents = selectedView == ViewMode::Daily ? mainView.getDailyEvents() : mainView.getWeeklyEvents();
    Event *newEvent = new Event(event);
    currentEvents.push_back(newEvent);
    if (selectedView == ViewMode::Daily)
        mainView.setDailyEvents(currentEvents);
    else
        mainView.setWeeklyEvents(currentEvents);
}

/* --------------------------------- Getters -------------------------------- */
bool MainController::getIsMenuHearing()
{
    return this->isMenuHearing;
}

/* --------------------------------- Setters -------------------------------- */
void MainController::setSelectedView(ViewMode value)
{
    this->selectedView = value;
}

void MainController::setIsMenuHearing(bool value)
{
    this->isMenuHearing = value;
}
