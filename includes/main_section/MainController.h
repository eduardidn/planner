#ifndef VIEW_CONTROLLER_H
#define VIEW_CONTROLLER_H

#include "models/IController.h"
#include "models/Event.h"
#include "main_section/MainView.h"

#include <vector>

class MainController : public IController
{

private:
    bool isMenuHearing = false;
    MainView mainView;
    function<void(function<void(Event)>)> onCreateViewCallback;
    function<void(const vector<Event *> &events)> onEditViewCallback;

public:
    MainController(function<void(function<void(Event)>)> createViewCb, function<void(const vector<Event *> &events)> editViewCb);
    enum ViewMode
    {
        Daily,
        Weekly
    };
    ViewMode selectedView;
    void whileUserMenuSelection() override;
    void handleDisplay() override;
    void handleDisplayWeeklyView();
    void switchViews();
    void addEvent(const Event &event);

    /* --------------------------------- Getters -------------------------------- */
    bool getIsMenuHearing();

    /* --------------------------------- Setters -------------------------------- */
    void setSelectedView(ViewMode value);
    void setIsMenuHearing(bool value);
};

#endif // VIEW_CONTROLLER_H