#include "DebugBox.h"

DebugBox::DebugBox(): Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL) {

    timeLabel= new Gtk::Label("test");
    timeLabel->override_font(*(new Pango::FontDescription("sans bold 18")));

    this->pack_start(*timeLabel, false, true, 0);
}