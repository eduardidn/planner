#ifndef DELETE_VIEW_H
#define DELETE_VIEW_H

#include "models/IView.h"
#include "models/Event.h"

#include <vector>

class DeleteView : public IView
{
public:
    void display() override;
    void displayMenuOptions() override;
    void displayEvents(const vector<Event *> &events);
    void displayEventFields(const Event &event);
};

#endif // DELETE_VIEW_H