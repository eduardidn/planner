#include "database/repositories/EventRepository.h"
#include "database/connection/DatabaseManager.h"
#include <iostream>
#include <string>

using namespace std;

EventRepository::EventRepository(DatabaseManager &dbManager) : db(dbManager) {}

pqxx::result EventRepository::listDailyEvents()
{
    pqxx::result results = db.executeQuery("SELECT * FROM events WHERE event_date = CURRENT_DATE ORDER BY event_date ASC, event_time ASC;");
    return results;
}

pqxx::result EventRepository::listWeeklyEvents()
{
    pqxx::result results = db.executeQuery("SELECT * FROM events WHERE event_date >= date_trunc('week', CURRENT_DATE)AND event_date < date_trunc('week', CURRENT_DATE) + interval '1 week' ORDER BY event_date ASC, event_time ASC;");
    return results;
}

void EventRepository::addEvent(const string &name, const string &date)
{
    string query = "INSERT INTO events (name, date) VALUES ('" + name + "', '" + date + "');";
    db.executeQuery(query);
}

void EventRepository::editEvent(int id, const string &name, const string &date)
{
    string query = "UPDATE events SET name = '" + name + "', date = '" + date + "' WHERE id = " + to_string(id) + ";";
    db.executeQuery(query);
}
