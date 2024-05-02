#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <pqxx/pqxx>

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    pqxx::result executeQuery(const std::string &query);
    bool isConnected() const;

private:
    pqxx::connection *connection;
};

#endif // DATABASE_MANAGER_H