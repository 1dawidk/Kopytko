#ifndef KOPYTKO_NOTIFICATIONLISTVIEW_H
#define KOPYTKO_NOTIFICATIONLISTVIEW_H


#include <gtkmm/box.h>
#include <vector>
#include <Logic/Notification.h>
#include "NotificationEntryView.h"

using namespace std;

class NotificationListView : public Gtk::VBox {
public:
    NotificationListView(vector<Notification*> *notifs);
    void notifyChange();
private:

    vector<Notification*> *notifs;
    vector<NotificationEntryView*> notifViews;
};


#endif //KOPYTKO_NOTIFICATIONLISTVIEW_H
