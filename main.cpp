#include <iostream>
#include "HWDrivers/Camera.h"
#include "AI/FaceRecognizer.h"
#include <gtkmm.h>
#include "UI/Context.h"
#include "curl/curl.h"


int main(int argc, char *argv[]) {
    Glib::thread_init();
    Gtk::Main kit(argc, argv);

    curl_global_init(CURL_GLOBAL_ALL);

    MainContext mainContext(argv[0]);
    mainContext.init();

    Gtk::Main::run(mainContext);

    return 0;
}