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
    optional<Event> eventToEdit;
    function<void()> onShowMainViewCallback;
    function<void()> onEditEventCallback;

public:
    EditController(function<void()> mainViewCb);
    void whileUserMenuSelection() override;
    void handleDisplay() override;
    void selectEventHearing();
    void setEventToEditFromIndex(const int &index);
    void setEventToEdit(const Event &event);

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
    void setOnEditEventCallback(function<void()> cb);
    void setEvents(const vector<Event *> &events);
};

#endif // EDIT_CONTROLLER_H