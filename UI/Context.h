#ifndef KOPYTKO_CONTEXT_H
#define KOPYTKO_CONTEXT_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/main.h>
#include <gdkmm/screen.h>
#include <fstream>
#include <iostream>

using namespace std;

#define OPEN_FILE_MODE_RELATIVE 0
#define OPEN_FILE_MODE_ABSOLUTE 1

#define CONTEXT_VERTICAL    0
#define CONTEXT_HORIZONTAL  1

class Context : public Gtk::Window{
public:
    explicit Context();
    virtual void init();
    void setContextView(Gtk::Box *view);

private:
};


#endif //KOPYTKO_CONTEXT_H
