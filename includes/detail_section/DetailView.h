#ifndef DETAIL_VIEW_H
#define DETAIL_VIEW_H

#include "models/IView.h"
#include "models/Event.h"

class DetailView : public IView
{
public:
    void display() override;
    void displayMenuOptions() override;

    /* --------------------------------- Helpers -------------------------------- */
    void displayEventFields(const Event &event);
};

#endif // DETAIL_VIEW_H