#ifndef EXCEPTIONS_UTILS_H
#define EXCEPTIONS_UTILS_H

#include <iostream>
#include <functional>
#include <pqxx/pqxx>

using namespace std;

template <typename T>
void handleFunctionErrorsAndExit(function<T()> func)
{
    try
    {
        func();
    }
    catch (const pqxx::sql_error &e)
    {
        cerr << "SQL error: " << e.what() << endl;
        throw;
    }
    catch (const exception &e)
    {
        cerr << "Standard exception: " << e.what() << endl;
        throw;
    }
    catch (...)
    {
        cerr << "Unknown exception occurred" << endl;
        throw;
    }
};

#endif // EXCEPTIONS_UTILS_H