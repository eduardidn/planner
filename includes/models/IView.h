#ifndef I_VIEW_H
#define I_VIEW_H

class IView {
public:
    virtual ~IView() {}  // Trivial virtual destructor with a definition
    virtual void display() = 0;
};

#endif