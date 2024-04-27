#ifndef EDIT_VIEW_H
#define EDIT_VIEW_H

#include "models/IView.h"
#include "models/Event.h"

#include <vector>

class EditView : public IView
{
public:
    void display() override;
    void displayMenuOptions() override;
    void displayEvents(const vector<Event *> &events);

    /* --------------------------------- Helpers -------------------------------- */
    void displayEventFields(map<string, string> event);
};

#endif // EDIT_VIEW_H