#include "NotificationEntryView.h"

NotificationEntryView::NotificationEntryView(Notification &phoneNoti) {
    titleLabel.set_label(phoneNoti.getTitle());
    textLabel.set_label(phoneNoti.getText());

    switch (phoneNoti.getFrom()){
        case NOTIFICATION_FROM_PHONE:
            fromLabel.set_label("Phone:");
            break;
        case NOTIFICATION_FROM_HOME:
            fromLabel.set_label("Home:");
            break;
        case NOTIFICATION_FROM_MIRROR:
            fromLabel.set_label("Mirror:");
            break;
    }

    prepareView();
}

void NotificationEntryView::prepareView() {
    fromLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_TOP);
    titleLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_TOP);
    textLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_TOP);

    this->pack_start(fromLabel, false, false);
    this->pack_start(titleLabel, false, false);
    this->pack_start(textLabel, false, false);

    this->show_all_children(true);
    this->show();
}
