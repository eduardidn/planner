#include "models/ViewManager.h"
#include "database/connection/DatabaseManager.h"
#include "database/repositories/EventRepository.h"

#include <iostream>

int main()
{
    DatabaseManager dbManager;
    EventRepository eventRepository(dbManager);
    ViewManager viewManager(eventRepository);

    return 0;
}