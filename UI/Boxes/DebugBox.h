#ifndef KOPYTKO_DEBUGBOX_H
#define KOPYTKO_DEBUGBOX_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <pangomm/fontdescription.h>

class DebugBox : public Gtk::Box {
private:
    Gtk::Label *timeLabel;

public:
    DebugBox();
};


#endif //KOPYTKO_DEBUGBOX_H
