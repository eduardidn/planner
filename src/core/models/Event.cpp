#include "models/Event.h"
#include "database/repositories/EventRepository.h"
#include "utils/ExceptionUtils.h"

#include <map>
#include <string>
#include <iostream>
using namespace std;

Event::Event(const int &id, const string &title, const string &description, const string &date, const string &time, const string &frequency, const string &priority, EventRepository &eventRepository) : repository(eventRepository)
{
    this->id = id;
    this->title = title;
    this->description = description;
    this->date = date;
    this->time = time;
    this->frequency = frequency;
    this->priority = priority;
    this->eventFields = {
        {"title", &Event::title},
        {"description", &Event::description},
        {"date", &Event::date},
        {"time", &Event::time},
        {"frequency", &Event::frequency},
        {"priority", &Event::priority}};
}

Event::Event(map<string, string> eventMap, EventRepository &eventRepository) : repository(eventRepository)
{
    this->eventFields = {
        {"title", &Event::title},
        {"description", &Event::description},
        {"date", &Event::date},
        {"time", &Event::time},
        {"frequency", &Event::frequency},
        {"priority", &Event::priority}};
    for (const auto &[key, value] : eventMap)
    {
        if (this->eventFields.find(key) != this->eventFields.end())
        {
            this->*(this->eventFields[key]) = value;
        }
    }
}

void Event::saveEvent()
{
    cout << "Saving event..." << endl;
    handleFunctionErrorsAndExit<void>([this]()
                                      { repository.addEvent(this->title, this->description, this->date, this->time, this->frequency, this->priority); });
}

void Event::editEvent(const map<string, string> &changes)
{
    for (const auto &[key, value] : changes)
    {
        if (this->eventFields.find(key) != this->eventFields.end())
        {
            this->*(this->eventFields[key]) = value;
        }
    }
    cout << "Saving changes..." << endl;
    handleFunctionErrorsAndExit<void>([this]()
                                      { repository.editEvent(this->id, this->title, this->description, this->date, this->time, this->frequency, this->priority); });
}

void Event::deleteEvent()
{
    cout << "Deleting event..." << endl;
    handleFunctionErrorsAndExit<void>([this]()
                                      { repository.deleteEvent(this->id); });
}

/* -------------------------------------------------------------------------- */
/*                                   Setters                                  */
/* -------------------------------------------------------------------------- */
void Event::setId(const int &id)
{
    this->id = id;
}

/* -------------------------------------------------------------------------- */
/*                                   Getters                                  */
/* -------------------------------------------------------------------------- */
int Event::getId() const
{
    return this->id;
}

string Event::getTitle() const
{
    return this->title;
}

string Event::getDescription() const
{
    return this->description;
}

string Event::getDate() const
{
    return this->date;
}

string Event::getTime() const
{
    return this->time;
}

string Event::getFrequency() const
{
    return this->frequency;
}

string Event::getPriority() const
{
    return this->priority;
}
