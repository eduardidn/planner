#include "models/ViewManager.h"

ViewManager::ViewManager() : mainController([this]()
                                            { this->showCreateView(); }),
                             createController([this]()
                                              { this->showMainView(); }) {}

void ViewManager::showMainView()
{
    mainController.handleDisplay();
}

void ViewManager::showCreateView()
{
    createController.handleDisplay();
}