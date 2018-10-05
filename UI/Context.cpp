#include "Context.h"

int Context::winW=0;
int Context::winH=0;

Context::Context(string runPath) {
    //Get build DIRECTORY not app run path
    size_t lastSlash= runPath.find_last_of('/');
    buildPath= runPath.substr(0, lastSlash);
    buildPath+="/..";
}

void Context::init() {
    Glib::RefPtr<Gdk::Screen> screen= Gdk::Screen::get_default();
    winW= screen->get_width();
    winH= screen->get_height();
}

void Context::setContextView(Gtk::Box *view) {
    this->add(*view);
}

ofstream Context::openWriteFile(string path, int mode) {
    ofstream file;

    if(mode==OPEN_FILE_MODE_RELATIVE) {
        file.open(buildPath + path, ios::out | ios::trunc);
    } else {
        char rpath[255];
        realpath(path.c_str(), rpath);
        file.open(rpath, ios::out | ios::trunc);
    }

    return file;
}

ifstream Context::openReadFile(string path, int mode) {
    ifstream file;

    if(mode==OPEN_FILE_MODE_RELATIVE) {
        file.open(buildPath + path, ios::in);
    } else {
        char rpath[255];
        realpath(path.c_str(), rpath);
        file.open(rpath, ios::in);
    }

    return file;
}

int Context::prcToPix(int prc, int dir) {
   if(dir==CONTEXT_VERTICAL)
       return (prc*winH)/100;
   else if(dir==CONTEXT_HORIZONTAL)
       return (prc*winW)/100;
}

string Context::getRealPath(string path) {
    return buildPath+path;
}
