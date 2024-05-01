#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "models/IView.h"
#include "models/Event.h"

#include <vector>

class MainView : public IView
{
private:
    vector<Event *> dailyEvents;
    vector<Event *> weeklyEventMain;

public:
    MainView();
    void display() override;
    void displayMenuOptions() override;
    void displayWeeklyView();

    /* --------------------------------- Helpers -------------------------------- */
    void displayTable(const vector<Event *> &events);
    string truncate(const string &str, int width);

    /* --------------------------------- Getters -------------------------------- */
    vector<Event *> getDailyEvents();
    vector<Event *> getWeeklyEvents();

    /* --------------------------------- Setters -------------------------------- */
    void setDailyEvents(vector<Event *> events);
    void setWeeklyEvents(vector<Event *> events);
};

#endif // MAIN_VIEW_H