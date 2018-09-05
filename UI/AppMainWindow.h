#ifndef KOPYTKO_APPMAINWINDOW_H
#define KOPYTKO_APPMAINWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <UI/Views/ClockView.h>

class AppMainWindow : public Gtk::Window{
public:
    void init();

private:
    Gtk::Box *box;

    //Views
    ClockView *clockView;
};


#endif //KOPYTKO_APPMAINWINDOW_H
