#include "models/ViewManager.h"

ViewManager::ViewManager(EventRepository &eventRepository)
    : mainController(
          eventRepository, [this](function<void()> addEventCallback)
          { this->showCreateView(addEventCallback); },
          [this](function<void()> editEventCallback, const vector<Event *> &events)
          { this->showEditView(editEventCallback, events); },
          [this](function<void()> deleteEventCallback, const vector<Event *> &events)
          { this->showDeleteView(deleteEventCallback, events); }),
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

void ViewManager::showEditView(function<void()> editEventCb, const vector<Event *> &events)
{
    editController.setEvents(events);
    editController.setOnEditEventCallback(editEventCb);
    editController.handleDisplay();
}

void ViewManager::showDeleteView(function<void()> deleteEventCb, const vector<Event *> &events)
{
    deleteController.setEvents(events);
    deleteController.setOnDeleteEventCallback(deleteEventCb);
    deleteController.handleDisplay();
}