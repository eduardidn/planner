#include "models/ViewManager.h"
#include "database/connection/DatabaseManager.h"
#include "database/repositories/EventRepository.h"

#include <iostream>

int main()
{
    try
    {
        DatabaseManager dbManager;
        EventRepository eventRepository(dbManager);
        ViewManager viewManager(eventRepository);
    }
    catch (const exception &e)
    {
        cout << "An error occurred. Exiting..." << endl;
        cerr << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cout << "An error occurred. Exiting..." << endl;
        return 1;
    }

    return 0;
}