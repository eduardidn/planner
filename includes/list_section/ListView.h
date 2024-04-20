#ifndef LIST_VIEW_H
#define LIST_VIEW_H

#include "models/IView.h"


class ListView : public IView {
public:
    void display() override;
};

#endif // LIST_VIEW_H