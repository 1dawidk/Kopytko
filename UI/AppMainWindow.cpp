#include "AppMainWindow.h"


void AppMainWindow::init() {
    Gdk::Color bg_color("black");
    this->modify_bg(Gtk::STATE_NORMAL, bg_color);
    this->fullscreen();
}