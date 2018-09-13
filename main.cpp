#include <iostream>
#include "HWDrivers/Camera.h"
#include "AI/FaceRecognizer.h"
#include <gtkmm.h>
#include "UI/AppMainWindow.h"


int main(int argc, char *argv[]) {
    Glib::thread_init();
    Gtk::Main kit(argc, argv);

    AppMainWindow appMainWindow;
    appMainWindow.init();


    Gtk::Main::run(appMainWindow);

    return 0;
}