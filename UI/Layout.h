#ifndef KOPYTKO_LAYOUT_H
#define KOPYTKO_LAYOUT_H

#include <gtkmm/box.h>

class Layout : public Gtk::Box {
public:
    Layout();
private:
    Gtk::Box *headerBox;
    Gtk::Box *midBox;
    Gtk::Box *notiBox;
    Gtk::Box *midMidBox;
    Gtk::Box *rightMidBox;
    Gtk::Box *bottomBox;
};


#endif //KOPYTKO_LAYOUT_H
