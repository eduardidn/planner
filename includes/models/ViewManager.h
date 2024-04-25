#include "models/IView.h"
#include "main_section/MainController.h"
#include "create_section/CreateController.h"

class ViewManager
{
private:
    MainController mainController;
    CreateController createController;

public:
    ViewManager();
    void showMainView();
    void showCreateView();
};