#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include "models/IView.h"
#include "main_section/MainController.h"
#include "create_section/CreateController.h"
#include "edit_section/EditController.h"

class ViewManager
{
private:
    MainController mainController;
    CreateController createController;
    EditController editController;

public:
    ViewManager();
    void showMainView();
    void showCreateView(function<void(Event)>);
    void showEditView(const vector<Event *> &events);
};

#endif // VIEW_MANAGER_H