#ifndef KOPYTKO_HEADER_H
#define KOPYTKO_HEADER_H

#include <gtkmm/box.h>
#include "ClockView.h"

class Header : public Gtk::Box {
private:
    ClockView *clockView;

public:
    Header();
};


#endif //KOPYTKO_HEADER_H
