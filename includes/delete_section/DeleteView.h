#ifndef DELETE_VIEW_H
#define DELETE_VIEW_H

#include "models/IView.h"
#include "models/Event.h"

#include <vector>

class DeleteView : public IView
{
private:
    Event *selectedEvent;

public:
    DeleteView() : selectedEvent(nullptr) {}
    void display() override;
    void displayMenuOptions() override;
    void displayEvents(const vector<Event *> &events);

    /* --------------------------------- Setters -------------------------------- */
    void setSelectedEvent(Event *event);
};

#endif // DELETE_VIEW_H