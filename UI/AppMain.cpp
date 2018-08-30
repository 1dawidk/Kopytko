#include "AppMain.h"

using namespace std;

AppMain::AppMain(string title) : Gtk::Application("pl.dawidkulpa.surviveworldcreator") {
    w=new Gtk::Window();
    w->set_title(title);
}

Glib::RefPtr<AppMain> AppMain::create(string title) {
    return Glib::RefPtr<AppMain>(new AppMain(title));
}

Gtk::Window* AppMain::getMainWindow(){
    return w;
}

void AppMain::on_startup() {
    Application::on_startup();

    b= new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);

    //Prepare initial main box layout
    clockView= new ClockView();
    b->pack_start(*clockView, false, true, 0);

    w->maximize();
    w->fullscreen();
    w->override_background_color(Gdk::RGBA("balck"));

    //Add main box for main window
    w->add(*b);

    w->show_all();
}
