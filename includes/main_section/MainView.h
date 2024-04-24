#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "models/IView.h"
#include "models/Event.h"

#include <vector>

class MainView : public IView
{
public:
    void display() override;
    void displayMenuOptions() override;
    void displayWeeklyView();

    /* --------------------------------- Helpers -------------------------------- */
    void displayTable(vector<Event> eventMain);
};

#endif // MAIN_VIEW_H