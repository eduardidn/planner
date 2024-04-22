#include "models/Event.h"

#include <map>
#include <string>
using namespace std;

Event::Event(const string& name, const string& description, const string& date, const string& time, const string& recurrence, const string& priority) {
    this->name = name;
    this->description = description;
    this->date = date;
    this->time = time;
    this->recurrence = recurrence;
    this->priority = priority;
    this->event_fields = {
        {"name", &Event::name},
        {"description", &Event::description},
        {"date", &Event::date},
        {"time", &Event::time},
        {"recurrence", &Event::recurrence},
        {"priority", &Event::priority}
    };
}


void Event::saveEvent() {
    // save the event on the DB
}

void Event::editEvent(const map<string, string>& changes) {
    for (const auto& [key, value] : changes) {
        if (this->event_fields.find(key) != this->event_fields.end()) {
            this->*(this->event_fields[key]) = value;
        }
    }
}

void Event::deleteEvent() {
    // delete the event on the DB
}

/* -------------------------------------------------------------------------- */
/*                                   Getters                                  */
/* -------------------------------------------------------------------------- */

string Event::getName() const {
    return this->name;
}

string Event::getDescription() const {
    return this->description;
}

string Event::getDate() const {
    return this->date;
}

string Event::getTime() const {
    return this->time;
}

string Event::getRecurring() const {
    return this->recurrence;
}

string Event::getPriority() const {
    return this->priority;
}

