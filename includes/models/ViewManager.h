#include "models/IView.h"
#include "main_section/MainController.h"

class ViewManager
{
public:
    void showView(IView *view);
    void showMainView();

private:
    IView *currentView;
    MainController mainController;
};