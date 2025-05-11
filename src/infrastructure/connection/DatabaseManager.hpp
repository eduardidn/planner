#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <pqxx/pqxx>
#include <string>

class DatabaseManager
{
public:
    static DatabaseManager &getInstance()
    {
        static DatabaseManager instance;
        return instance;
    }

    pqxx::connection *getConnection();
    bool isConnected() const;

private:
    DatabaseManager();
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager &) = delete;
    DatabaseManager &operator=(const DatabaseManager &) = delete;

    pqxx::connection *connection;
    void loadDotenv(const std::string &filename);
};

#endif // DATABASE_MANAGER_HPP
