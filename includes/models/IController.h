#ifndef I_CONTROLLER_H
#define I_CONTROLLER_H

class IController
{
public:
    virtual void handleDisplay() = 0;
    virtual void whileUserMenuSelection() = 0;
};

#endif // I_CONTROLLER_H