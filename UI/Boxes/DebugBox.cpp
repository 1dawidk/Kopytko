#include "DebugBox.h"

DebugBox::DebugBox(): Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL) {
    timeLabel= new Gtk::Label("test");
}