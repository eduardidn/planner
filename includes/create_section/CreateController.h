#ifndef CREATE_CONTROLLER_H
#define CREATE_CONTROLLER_H

#include "models/IController.h"
#include "models/Event.h"
#include "create_section/CreateView.h"
#include "database/repositories/EventRepository.h"

class CreateController : public IController
{

private:
    bool isMenuHearing = false;
    CreateView createView;
    map<string, string> newEventFields;
    function<void()> onShowMainViewCallback;
    function<void()> onCreateEventCallback;
    EventRepository &repository;

public:
    CreateController(EventRepository &EventRepository, function<void()> mainViewCb);
    void whileUserMenuSelection() override;
    void handleDisplay() override;

    /* --------------------------------- Helpers -------------------------------- */
    void setEventStringField(const string &field, const string &value);
    void setEventDateField();
    void setEventTimeField();
    void setEventFrequencyField();
    void setEventPriorityField();
    void saveEvent();
    void redirectToMainView();
    void resetState();

    /* --------------------------------- Getters -------------------------------- */
    bool getIsMenuHearing();

    /* --------------------------------- Setters -------------------------------- */
    void setIsMenuHearing(bool value);
    void setOnCreateEventCallback(function<void()> cb);
};

#endif // CREATE_CONTROLLER_H