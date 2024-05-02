#ifndef DELETE_CONTROLLER_H
#define DELETE_CONTROLLER_H

#include "models/IController.h"
#include "models/Event.h"
#include "delete_section/DeleteView.h"

class DeleteController : public IController
{

private:
    bool isMenuHearing = false;
    DeleteView deleteView;
    vector<Event *> events;
    optional<Event> eventToDelete;
    function<void()> onShowMainViewCallback;
    function<void()> onDeleteEventCallback;

public:
    DeleteController(function<void()> mainViewCb);
    void whileUserMenuSelection() override;
    void handleDisplay() override;
    void selectEventHearing();
    void setEventToDeleteFromIndex(const int &index);
    void setEventToDelete(const Event &event);

    /* --------------------------------- Helpers -------------------------------- */
    void deleteEvent();
    void goBackToList();
    void redirectToMainView();
    void resetState();

    /* --------------------------------- Setters -------------------------------- */
    void setEvents(const vector<Event *> &events);
    void setOnDeleteEventCallback(function<void()> cb);
};

#endif // DELETE_CONTROLLER_H