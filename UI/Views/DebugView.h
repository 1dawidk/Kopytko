#ifndef KOPYTKO_DEBUGVIEW_H
#define KOPYTKO_DEBUGVIEW_H

#include <gtkmm/label.h>
#include <string>
#include <vector>

using namespace std;

class DebugView : public Gtk::Label {
public:
    DebugView(int maxLines);
    void log(string msg);

private:
    int maxLines;
    vector<string> msgs;
    Glib::Dispatcher dispatcher;

    void onLog();
};


#endif //KOPYTKO_DEBUGVIEW_H
