#include "models/ViewManager.h"

ViewManager::ViewManager(EventRepository &eventRepository)
    : mainController(
          eventRepository, [this](function<void()> addEventCallback)
          { this->showCreateView(addEventCallback); },
          [this](function<void()> editEventCallback, const vector<Event *> &events)
          { this->showEditView(editEventCallback, events); },
          [this](function<void()> deleteEventCallback, const vector<Event *> &events)
          { this->showDeleteView(deleteEventCallback, events); },
          [this](function<void()> detailEventCallback, const Event &event)
          { this->showDetailView(detailEventCallback, event); }),
      createController(eventRepository, [this]()
                       { this->showMainView(); }),
      editController([this]()
                     { this->showMainView(); }),
      deleteController([this]()
                       { this->showMainView(); }),
      detailController(
          [this]()
          { this->showMainView(); },
          [this](function<void()> editEventCallback, const Event &event)
          { this->showEditViewFromDetails(editEventCallback, event); },
          [this](function<void()> deleteEventCallback, const Event &event)
          { this->showDeleteViewFromDetails(deleteEventCallback, event); })
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

void ViewManager::showEditViewFromDetails(function<void()> editEventCb, const Event &event)
{
    editController.setOnEditEventCallback(editEventCb);
    editController.setEventToEdit(event);
}

void ViewManager::showDeleteViewFromDetails(function<void()> deleteEventCb, const Event &event)
{
    deleteController.setOnDeleteEventCallback(deleteEventCb);
    deleteController.setEventToDelete(event);
}

void ViewManager::showDetailView(function<void()> reloadCb, const Event &event)
{
    detailController.setEvent(event);
    detailController.setOnReloadCallback(reloadCb);
    detailController.handleDisplay();
}