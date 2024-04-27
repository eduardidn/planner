#ifndef EDIT_CONTROLLER_H
#define EDIT_CONTROLLER_H

#include "models/IController.h"
#include "models/Event.h"
#include "edit_section/EditView.h"

class EditController : public IController
{

private:
    bool isMenuHearing = false;
    EditView editView;
    vector<Event *> events;
    map<string, string> EventToEditFields;
    int eventIndex = -1;
    function<void()> onShowMainViewCallback;

public:
    EditController(function<void()> mainViewCb);
    void whileUserMenuSelection() override;
    void handleDisplay() override;
    void selectEventHearing();
    void setEventToEdit(const int &id);

    /* --------------------------------- Helpers -------------------------------- */
    void setEventStringField(const string &field, const string &value);
    void setEventDateField();
    void setEventTimeField();
    void setEventFrequencyField();
    void setEventPriorityField();
    void editEvent();
    void redirectToMainView();
    void resetState();

    /* --------------------------------- Getters -------------------------------- */
    bool getIsMenuHearing();

    /* --------------------------------- Setters -------------------------------- */
    void setIsMenuHearing(bool value);
    void setEvents(const vector<Event *> &events);
};

#endif // EDIT_CONTROLLER_H