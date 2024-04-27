#include "models/Event.h"

#include <map>
#include <string>
using namespace std;

Event::Event(const string &title, const string &description, const string &date, const string &time, const string &frequency, const string &priority)
{
    this->title = title;
    this->description = description;
    this->date = date;
    this->time = time;
    this->frequency = frequency;
    this->priority = priority;
    this->event_fields = {
        {"title", &Event::title},
        {"description", &Event::description},
        {"date", &Event::date},
        {"time", &Event::time},
        {"frequency", &Event::frequency},
        {"priority", &Event::priority}};
}

Event::Event(const int &id, const string &title, const string &description, const string &date, const string &time, const string &frequency, const string &priority)
{
    this->id = id;
    this->title = title;
    this->description = description;
    this->date = date;
    this->time = time;
    this->frequency = frequency;
    this->priority = priority;
    this->event_fields = {
        {"title", &Event::title},
        {"description", &Event::description},
        {"date", &Event::date},
        {"time", &Event::time},
        {"frequency", &Event::frequency},
        {"priority", &Event::priority}};
}

void Event::saveEvent()
{
    // save the event on the DB
}

void Event::editEvent(const map<string, string> &changes)
{
    for (const auto &[key, value] : changes)
    {
        if (this->event_fields.find(key) != this->event_fields.end())
        {
            this->*(this->event_fields[key]) = value;
        }
    }
}

void Event::deleteEvent()
{
    // delete the event on the DB
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
