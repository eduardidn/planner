#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "models/IController.h"
#include "models/Event.h"
#include "main_section/MainView.h"

class MainController : public IController
{

private:
    bool isMenuHearing = false;
    MainView mainView;

public:
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

    /* --------------------------------- Getters -------------------------------- */
    bool getIsMenuHearing();

    /* --------------------------------- Setters -------------------------------- */
    void setSelectedView(ViewMode value);
    void setIsMenuHearing(bool value);
};

#endif // MAIN_CONTROLLER_H