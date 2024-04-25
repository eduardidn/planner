#ifndef CREATE_VIEW_H
#define CREATE_VIEW_H

#include "models/IView.h"
#include "models/Event.h"

#include <vector>

class CreateView : public IView
{
public:
    void display() override;
    void displayMenuOptions() override;

    /* --------------------------------- Helpers -------------------------------- */
    void displayEventFields(map<string, string> newEvent);
    void clearView();
};

#endif // CREATE_VIEW_H