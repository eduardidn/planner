#ifndef EVENT_H
#define EVENT_H

#include <map>
#include <string>
using namespace std;

class Event
{
private:
    int id;
    string title;
    string description;
    string date;
    string time;
    string frequency;
    string priority;
    map<string, string Event::*> event_fields;

public:
    Event(const string &title, const string &description, const string &date, const string &time, const string &frequency, const string &priority);
    Event(const int &id, const string &title, const string &description, const string &date, const string &time, const string &frequency, const string &priority);
    // used for creating a new event on the DB
    void saveEvent();
    // used for delete the event on the DB and on the object itself
    void editEvent(const map<string, string> &changes);
    // used for delete the event on the DB
    void deleteEvent();

    /* -------------------------------------------------------------------------- */
    /*                                   Setters                                  */
    /* -------------------------------------------------------------------------- */
    void setId(const int &id);

    /* -------------------------------------------------------------------------- */
    /*                                   getters                                  */
    /* -------------------------------------------------------------------------- */
    int getId() const;
    string getTitle() const;
    string getDescription() const;
    string getDate() const;
    string getTime() const;
    string getFrequency() const;
    string getPriority() const;
};

#endif // EVENT_H