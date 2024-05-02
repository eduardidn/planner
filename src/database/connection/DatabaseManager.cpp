#include "database/connection/DatabaseManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// provisional way to use env variables without using dot-env
void loadDotenv(const string &filename)
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
    cout << "Connecting to the database..." << endl;
    loadDotenv(".env");
    string dbname = getenv("DB_NAME");
    string user = getenv("DB_USER");
    string password = getenv("DB_PASSWORD");
    string hostaddr = getenv("DB_HOST");
    string port = getenv("DB_PORT");

    try
    {
        string connection_string = "dbname=" + dbname + " user=" + user +
                                   " password=" + password + " hostaddr=" + hostaddr + " port=" + port;
        connection = new pqxx::connection(connection_string);
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
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

pqxx::result DatabaseManager::executeQuery(const string &query)
{
    pqxx::work trans(*connection, "trans");

    pqxx::result res = trans.exec(query);

    trans.commit();
    return res;
}

bool DatabaseManager::isConnected() const
{
    return connection->is_open();
}