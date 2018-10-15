#include <iostream>
#include "Logic/HWDrivers/Camera.h"
#include "Logic/AI/FaceRecognizer.h"
#include <gtkmm/main.h>
#include "curl/curl.h"


int main(int argc, char *argv[]) {
    Glib::thread_init();
    Gtk::Main kit(argc, argv);

    curl_global_init(CURL_GLOBAL_ALL);

    DataProcessor dataProcessor(argv[0]);

    UI ui(&dataProcessor);
    ui.init();

    Gtk::Main::run(ui);

    return 0;
}