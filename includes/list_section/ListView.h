#ifndef LIST_VIEW_H
#define LIST_VIEW_H

#include "models/IView.h"
#include "models/Event.h"

class ListView : public IView
{

private:
    bool isMenuHearing = false;

public:
    enum ViewMode
    {
        Daily,
        Weekly
    };
    ViewMode selectedView;

    void display() override;
    void displayMenuOptions() override;
    void whileUserMenuSelection() override;

    void displayWeeklyView();
    void switchViews();

    /* --------------------------------- Getters -------------------------------- */
    bool getIsMenuHearing();

    /* --------------------------------- Setters -------------------------------- */
    void setSelectedView(ViewMode value);
    void setIsMenuHearing(bool value);

    /* --------------------------------- Helpers -------------------------------- */
    void displayTable(vector<Event> eventList);
};

#endif // LIST_VIEW_H