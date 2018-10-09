#include <iostream>
#include "Logic/HWDrivers/Camera.h"
#include "Logic/AI/FaceRecognizer.h"
#include <gtkmm/main.h>
#include "UI/Context.h"
#include "curl/curl.h"


int main(int argc, char *argv[]) {
    Glib::thread_init();
    Gtk::Main mainLoop(argc, argv);

    curl_global_init(CURL_GLOBAL_ALL);

    MainContext mainContext(argv[0]);
    mainContext.init();

    Gtk::Main::run(mainContext);

    return 0;
}