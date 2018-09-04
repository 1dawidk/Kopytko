#ifndef KOPYTKO_CLOCKVIEW_H
#define KOPYTKO_CLOCKVIEW_H


#include <stdlib.h>
#include <gtkmm/label.h>
#include "../../Misc/Thread.h"
#include "../../Misc/Clock.h"
#include <string>

using namespace std;

class ClockView : public Gtk::Label, Thread {
public:
    ClockView();
    ~ClockView();

private:
    void run() override;

    void stop() override;
};


#endif //KOPYTKO_CLOCKVIEW_H
