#ifndef VIEW_CONTROLLER_H
#define VIEW_CONTROLLER_H

#include "models/IController.h"
#include "models/Event.h"
#include "main_section/MainView.h"
#include "database/repositories/EventRepository.h"

#include <vector>

class MainController : public IController
{

private:
    bool isMenuHearing = false;
    MainView mainView;
    function<void(function<void()>)> onCreateViewCallback;
    function<void(function<void()>, const vector<Event *> &events)> onEditViewCallback;
    function<void(function<void()>, const vector<Event *> &events)> onDeleteViewCallback;
    function<void(function<void()>, const Event &event)> onDetailViewCallback;
    EventRepository &repository;

public:
    MainController(EventRepository &eventRepository, function<void(function<void()>)> createViewCb, function<void(function<void()>, const vector<Event *> &events)> editViewCb, function<void(function<void()>, const vector<Event *> &events)> deleteViewCb, function<void(function<void()>, const Event &event)> detailViewCb);
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
    void reloadEvents();
    void handleDetailViewRedirect(const int &index);

    /* --------------------------------- Helpers -------------------------------- */
    void fetchDailyEvents();
    void fetchWeeklyEvents();
    vector<Event *> parseEvents(pqxx::result result);

    /* --------------------------------- Getters -------------------------------- */
    bool getIsMenuHearing();

    /* --------------------------------- Setters -------------------------------- */
    void setSelectedView(ViewMode value);
    void setIsMenuHearing(bool value);
};

#endif // VIEW_CONTROLLER_H