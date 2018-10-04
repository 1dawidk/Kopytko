#ifndef KOPYTKO_HEARTBEATVIEW_H
#define KOPYTKO_HEARTBEATVIEW_H

#include <gtkmm/label.h>
#include <string>

using namespace std;

class HeartbeatView : public Gtk::Label {
public:
    HeartbeatView();

    void makeBeat();
    void makeBeat(string msg);

    void onBeat();
private:
    string msg;
    int nBeat;
    Glib::Dispatcher beatDispatcher;
};


#endif //KOPYTKO_HEARTBEATVIEW_H
