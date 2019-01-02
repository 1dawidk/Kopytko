#ifndef KOPYTKO_NOTIFICATIONENTRYVIEW_H
#define KOPYTKO_NOTIFICATIONENTRYVIEW_H


#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <string>
#include <Logic/Notification.h>

using namespace std;

class NotificationEntryView : public Gtk::VBox {
public:
    NotificationEntryView(Notification &notif);
private:
    Gtk::Label fromLabel;
    Gtk::Label titleLabel;
    Gtk::Label textLabel;

    void prepareView();
};


#endif //KOPYTKO_NOTIFICATIONENTRYVIEW_H
