#include <iostream>
#include "HWDrivers/Camera.h"
#include "AI/FaceRecognizer.h"
#include <gtkmm.h>
#include "UI/Context.h"


int main(int argc, char *argv[]) {
    Glib::thread_init();
    Gtk::Main kit(argc, argv);

    Context appMainWindow;
    appMainWindow.init(argv[0]);


    Gtk::Main::run(appMainWindow);

    return 0;
}