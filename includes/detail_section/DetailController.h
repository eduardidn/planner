#ifndef DETAIL_CONTROLLER_H
#define DETAIL_CONTROLLER_H

#include "models/IController.h"
#include "models/Event.h"
#include "detail_section/DetailView.h"

class DetailController : public IController
{

private:
    bool isMenuHearing = false;
    DetailView detailView;
    optional<Event> event;
    function<void()> onReloadCb;
    function<void()> onShowMainViewCallback;
    function<void(function<void()>, Event &event)> onEditViewCallback;
    function<void(function<void()>, Event &event)> onDeleteViewCallback;

public:
    DetailController(function<void()> showMainViewCb, function<void(function<void()>, const Event &event)> editViewCb, function<void(function<void()>, const Event &event)> deleteViewCb);
    void whileUserMenuSelection() override;
    void handleDisplay() override;

    /* --------------------------------- Helpers -------------------------------- */
    void redirectToMainView();
    void redirectToEditView();
    void redirectToDeleteView();
    void resetState();
    void onEditCallback();
    void onDeleteCallback();

    /* --------------------------------- Getters -------------------------------- */
    bool getIsMenuHearing();

    /* --------------------------------- Setters -------------------------------- */
    void setIsMenuHearing(bool value);
    void setEvent(const Event &event);
    void setOnReloadCallback(const function<void()> &cb);
};

#endif // DETAIL_CONTROLLER_H