#ifndef EVENT_H
#define EVENT_H

#include <map>
#include <string>
using namespace std;


class Event {
private:
    string name;
    string description;
    string date;
    string time;
    string recurrence;
    string priority;
    map<string, string Event::*> event_fields;

public:
    Event(const string& name, const string& description, const string& date, const string& time, const string& recurrence, const string& priority);
    // used for creating a new event on the DB
    void saveEvent();
    // used for delete the event on the DB and on the object itself
    void editEvent(const map<string, string>& changes);
    // used for delete the event on the DB
    void deleteEvent();

    /* -------------------------------------------------------------------------- */
    /*                                   getters                                  */
    /* -------------------------------------------------------------------------- */
    string getName() const;
    string getDescription() const;
    string getDate() const;
    string getTime() const;
    string getRecurring() const;
    string getPriority() const;
};

#endif // EVENT_H