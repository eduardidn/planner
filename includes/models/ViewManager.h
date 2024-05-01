#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include "models/IView.h"
#include "database/repositories/EventRepository.h"
#include "main_section/MainController.h"
#include "create_section/CreateController.h"
#include "edit_section/EditController.h"
#include "delete_section/DeleteController.h"

class ViewManager
{
private:
    MainController mainController;
    CreateController createController;
    EditController editController;
    DeleteController deleteController;

public:
    ViewManager(EventRepository &eventRepository);
    void showMainView();
    void showCreateView(function<void(Event)>);
    void showEditView(const vector<Event *> &events);
    void showDeleteView(const vector<Event *> &events);
};

#endif // VIEW_MANAGER_H