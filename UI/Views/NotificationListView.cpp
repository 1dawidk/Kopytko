#include "NotificationListView.h"

NotificationListView::NotificationListView(vector<Notification*> *notifs) {
    this->notifs= notifs;
}

void NotificationListView::notifyChange() {
    //Remove previous notifs
    for(int i=0; i<notifViews.size(); i++){
        this->remove(*notifViews[i]);
        delete notifViews[i];
    }

    notifViews.clear();

    //Add new notifs
    for(int i=0; i<notifs->size(); i++){
        notifViews.push_back(new NotificationEntryView(*(*notifs)[i]));
        this->pack_end(*notifViews[i], false, false);
    }

    this->show_all_children(true);
    this->show();
};
