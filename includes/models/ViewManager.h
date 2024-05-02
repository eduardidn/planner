#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include "models/IView.h"
#include "database/repositories/EventRepository.h"
#include "main_section/MainController.h"
#include "create_section/CreateController.h"
#include "edit_section/EditController.h"
#include "delete_section/DeleteController.h"
#include "detail_section/DetailController.h"

class ViewManager
{
private:
    MainController mainController;
    CreateController createController;
    EditController editController;
    DeleteController deleteController;
    DetailController detailController;

public:
    ViewManager(EventRepository &eventRepository);
    void showMainView();
    void showCreateView(function<void()>);
    void showEditView(function<void()>, const vector<Event *> &events);
    void showDeleteView(function<void()>, const vector<Event *> &events);
    void showEditViewFromDetails(function<void()>, const Event &event);
    void showDeleteViewFromDetails(function<void()>, const Event &event);
    void showDetailView(function<void()>, const Event &event);
};

#endif // VIEW_MANAGER_H