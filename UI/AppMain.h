#ifndef KOPYTKO_APPMAIN_H
#define KOPYTKO_APPMAIN_H

#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <string>
#include "Boxes/DebugBox.h"

using namespace std;

class AppMain : public Gtk::Application {
private:
    Gtk::Window *w;
    Gtk::Box    *b;

    //Layout boxes
    DebugBox *debugBox;

public:
    AppMain(string title);
    Gtk::Window* getMainWindow();
    static Glib::RefPtr<AppMain> create(string title);

protected:
    virtual void on_startup() override;
};


#endif //KOPYTKO_APPMAIN_H
