#ifndef KOPYTKO_CONTEXT_H
#define KOPYTKO_CONTEXT_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
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
    explicit Context(string runPath);
    virtual void init();
    void setContextView(Gtk::Box *view);

    ofstream openWriteFile(string path, int mode);
    ifstream openReadFile(string path, int mode);
    string getRealPath(string path);

    static int prcToPix(int prc, int dir);

    static int winW;
    static int winH;



private:
    string buildPath;


};


#endif //KOPYTKO_CONTEXT_H
