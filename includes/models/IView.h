#ifndef I_VIEW_H
#define I_VIEW_H

class IView
{
public:
    virtual void display() = 0;
    virtual void displayMenuOptions() = 0;
};

#endif // I_VIEW_H