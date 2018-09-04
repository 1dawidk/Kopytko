#ifndef KOPYTKO_APPMAIN_H
#define KOPYTKO_APPMAIN_H

#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <string>
#include "Boxes/DebugBox.h"
#include "Views/ClockView.h"

using namespace std;

class AppMain : public Gtk::Application {
private:
    Gtk::Window *w;
    Gtk::Box    *b;

    //Layout boxes
    DebugBox *debugBox;

public:
    AppMain(string title);
    ~AppMain();
    Gtk::Window* getMainWindow();
    static Glib::RefPtr<AppMain> create(string title);

protected:
    virtual void on_startup() override;

    //Views
    ClockView *clockView;
};


#endif //KOPYTKO_APPMAIN_H
