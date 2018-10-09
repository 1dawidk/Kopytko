#ifndef KOPYTKO_CLOCKVIEW_H
#define KOPYTKO_CLOCKVIEW_H


#include <stdlib.h>
#include <gtkmm/label.h>
#include "Logic/Misc/Thread.h"
#include "Logic/Misc/Clock.h"
#include <string>

using namespace std;

class ClockView : public Gtk::Label{
public:
    ClockView();
    ~ClockView();

    void resize(int font_size);

private:
    Glib::Thread *worker;
    void work();
    bool workAct;
};


#endif //KOPYTKO_CLOCKVIEW_H
