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

void EventRepository::addEvent(const string &name, const string &description, const string &date, const string &time, const string &frequency, const string &priority)
{
    string query = "INSERT INTO events (title, description, event_date, event_time, frequency, priority) VALUES ('" + name + "', '" + description + "', '" + date + "', '" + time + "', '" + frequency + "', '" + priority + "');";
    db.executeQuery(query);
}

void EventRepository::editEvent(const int &id, const string &name, const string &description, const string &date, const string &time, const string &frequency, const string &priority)
{
    string query = "UPDATE events SET title = '" + name + "', description = '" + description + "', event_date = '" + date + "', event_time = '" + time + "', frequency = '" + frequency + "', priority = '" + priority + "' WHERE id = " + to_string(id) + ";";
    db.executeQuery(query);
}

void EventRepository::deleteEvent(const int &id)
{
    string query = "DELETE FROM events WHERE id = " + to_string(id) + ";";
    db.executeQuery(query);
}
