#include "models/ViewManager.h"

ViewManager::ViewManager()
    : mainController([this](function<void(Event)> eventCallback)
                     { this->showCreateView(eventCallback); },
                     [this](const vector<Event *> &events)
                     { this->showEditView(events); }),
      createController([this]()
                       { this->showMainView(); }),
      editController([this]()
                     { this->showMainView(); })
{
    mainController.handleDisplay();
}

void ViewManager::showMainView()
{
    mainController.handleDisplay();
}

void ViewManager::showCreateView(function<void(Event)> createEventCb)
{
    createController.setOnCreateEventCallback(createEventCb);
    createController.handleDisplay();
}

void ViewManager::showEditView(const vector<Event *> &events)
{
    editController.setEvents(events);
    editController.handleDisplay();
}