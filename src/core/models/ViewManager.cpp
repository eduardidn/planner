#include "models/ViewManager.h"

void ViewManager::showView(IView *view)
{
    currentView = view;
    currentView->display();
}

void ViewManager::showMainView()
{
    mainController.handleDisplay();
}