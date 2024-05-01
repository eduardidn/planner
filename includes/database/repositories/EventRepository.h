#ifndef EVENT_REPOSITORY_H
#define EVENT_REPOSITORY_H

#include "database/connection/DatabaseManager.h"

#include <string>
using namespace std;

class EventRepository
{
public:
    EventRepository(DatabaseManager &dbManager);
    pqxx::result listDailyEvents();
    pqxx::result listWeeklyEvents();
    void addEvent(const string &name, const string &description, const string &date, const string &time, const string &frequency, const string &priority);
    void editEvent(const int &id, const string &name, const string &description, const string &date, const string &time, const string &frequency, const string &priority);
    void deleteEvent(const int &id);

private:
    DatabaseManager &db;
};

#endif // EVENT_REPOSITORY_H