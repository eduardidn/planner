#ifndef CREATE_CONTROLLER_H
#define CREATE_CONTROLLER_H

#include "models/IController.h"
#include "models/Event.h"
#include "create_section/CreateView.h"

class CreateController : public IController
{

private:
    bool isMenuHearing = false;
    CreateView createView;
    map<string, string> newEventFields;
    function<void()> onShowMainViewCallback;

public:
    CreateController(std::function<void()> mainViewCb);
    void whileUserMenuSelection() override;
    void handleDisplay() override;

    /* --------------------------------- Helpers -------------------------------- */
    void setEventStringField(const string &field, const string &value);
    void setEventDateField();
    void setEventTimeField();
    void setEventFrequencyField();
    void setEventPriorityField();

    /* --------------------------------- Getters -------------------------------- */
    bool getIsMenuHearing();

    /* --------------------------------- Setters -------------------------------- */
    void setIsMenuHearing(bool value);
};

#endif // CREATE_CONTROLLER_H