#include "models/ViewManager.h"

ViewManager::ViewManager(EventRepository &eventRepository)
    : mainController(
          eventRepository, [this](function<void()> addEventCallback)
          { this->showCreateView(addEventCallback); },
          [this](const vector<Event *> &events)
          { this->showEditView(events); },
          [this](const vector<Event *> &events)
          { this->showDeleteView(events); }),
      createController(eventRepository, [this]()
                       { this->showMainView(); }),
      editController([this]()
                     { this->showMainView(); }),
      deleteController([this]()
                       { this->showMainView(); })
{
    mainController.handleDisplay();
}

void ViewManager::showMainView()
{
    mainController.handleDisplay();
}

void ViewManager::showCreateView(function<void()> createEventCb)
{
    createController.setOnCreateEventCallback(createEventCb);
    createController.handleDisplay();
}

void ViewManager::showEditView(const vector<Event *> &events)
{
    editController.setEvents(events);
    editController.handleDisplay();
}

void ViewManager::showDeleteView(const vector<Event *> &events)
{
    deleteController.setEvents(events);
    deleteController.handleDisplay();
}