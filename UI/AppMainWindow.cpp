#include "AppMainWindow.h"


void AppMainWindow::init() {
    Gdk::Color bg_color("black");

    box= new Gtk::VBox();

    //Create and add Views
    clockView= new ClockView();
    box->pack_start(*clockView);

    box->show_all_children(true);
    box->show();



    this->add(*box);
    this->modify_bg(Gtk::STATE_NORMAL, bg_color);
    this->fullscreen();
}