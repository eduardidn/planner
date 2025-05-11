#include "DatabaseManager.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void DatabaseManager::loadDotenv(const string &filename)
{
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        auto delimiterPos = line.find('=');
        auto name = line.substr(0, delimiterPos);
        auto value = line.substr(delimiterPos + 1);
        setenv(name.c_str(), value.c_str(), 1);
    }
}

DatabaseManager::DatabaseManager()
{
    cout << "[DatabaseManager] Connecting to the database..." << endl;
    loadDotenv(".env");

    string dbname = getenv("DB_NAME");
    string user = getenv("DB_USER");
    string password = getenv("DB_PASSWORD");
    string hostaddr = getenv("DB_HOST");
    string port = getenv("DB_PORT");

    try
    {
        string connection_string = "dbname=" + dbname +
                                   " user=" + user +
                                   " password=" + password +
                                   " host=" + hostaddr +
                                   " port=" + port;

        connection = new pqxx::connection(connection_string);

        if (connection->is_open())
        {
            cout << "[DatabaseManager] Connected successfully to: " << dbname << "@" << hostaddr << endl;
        }
        else
        {
            cerr << "[DatabaseManager] Connection failed." << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "[DatabaseManager] Error: " << e.what() << endl;
        throw;
    }
}

DatabaseManager::~DatabaseManager()
{
    if (connection->is_open())
    {
        connection->close();
    }
    delete connection;
}

pqxx::connection *DatabaseManager::getConnection()
{
    return connection;
}

bool DatabaseManager::isConnected() const
{
    return connection->is_open();
}
