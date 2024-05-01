#include "main_section/MainController.h"
#include "database/repositories/EventRepository.h"
#include "models/Event.h"
#include "utils/ConsoleUtils.h"
#include "utils/ExceptionUtils.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
using namespace std;

MainController::MainController(EventRepository &eventRepository, function<void(function<void(Event)>)> createViewCallback, function<void(const vector<Event *> &events)> editViewCb, function<void(const vector<Event *> &events)> deleteViewCb) : onCreateViewCallback(createViewCallback), onEditViewCallback(editViewCb), onDeleteViewCallback(deleteViewCb), repository(eventRepository)
{
}

void MainController::handleDisplay()
{
    setSelectedView(ViewMode::Daily);
    if (mainView.getDailyEvents().size() == 0)
    {
        auto fetchDailyEventsFunc = bind(&MainController::fetchDailyEvents, this);
        handleFunctionErrorsAndExit<void>(fetchDailyEventsFunc);
    }

    mainView.display();
    if (!isMenuHearing)
    {
        whileUserMenuSelection();
    }
}

void MainController::handleDisplayWeeklyView()
{
    setSelectedView(ViewMode::Weekly);
    if (mainView.getWeeklyEvents().size() == 0)
    {
        auto fetchWeeklyEventsFunc = bind(&MainController::fetchWeeklyEvents, this);
        handleFunctionErrorsAndExit<void>(fetchWeeklyEventsFunc);
    }

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
        {
            vector<Event *> events = selectedView == ViewMode::Daily ? mainView.getDailyEvents() : mainView.getWeeklyEvents();
            onDeleteViewCallback(events);
            break;
        }
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

/* --------------------------------- Helpers -------------------------------- */
void MainController::fetchDailyEvents()
{
    ConsoleUtils::clearScreen();
    cout << "Fetching events..." << endl;
    pqxx::result result = repository.listDailyEvents();
    vector<Event *> events = parseEvents(result);
    mainView.setDailyEvents(events);
}

void MainController::fetchWeeklyEvents()
{
    ConsoleUtils::clearScreen();
    cout << "Fetching events..." << endl;
    pqxx::result result = repository.listWeeklyEvents();
    vector<Event *> events = parseEvents(result);
    mainView.setWeeklyEvents(events);
}

vector<Event *> MainController::parseEvents(pqxx::result result)
{
    vector<Event *> events;
    for (const auto &event : result)
    {
        events.push_back(new Event(
            event["id"].as<int>(),
            event["title"].as<string>(),
            event["description"].as<string>(),
            event["event_date"].as<string>(),
            event["event_time"].as<string>(),
            event["frequency"].as<string>(),
            event["priority"].as<string>()));
    }
    return events;
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
