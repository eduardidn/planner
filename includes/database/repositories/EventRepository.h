#ifndef EVENT_REPOSITORY_H
#define EVENT_REPOSITORY_H

#include "database/connection/DatabaseManager.h"

class EventRepository
{
public:
    EventRepository(DatabaseManager &dbManager);
    pqxx::result listDailyEvents();
    pqxx::result listWeeklyEvents();
    void addEvent(const std::string &name, const std::string &date);
    void editEvent(int id, const std::string &name, const std::string &date);

private:
    DatabaseManager &db;
};

#endif // EVENT_REPOSITORY_H