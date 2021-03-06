#include <iostream>
#include <dkulpaclibs/hw/Camera.h>
#include "Logic/AI/FaceRecognition/FaceRecognizer.h"
#include <gtkmm/main.h>
#include "curl/curl.h"
#include <SDL/SDL.h>
#include <dkulpaclibs/misc/debug/Log.h>

int main(int argc, char *argv[]) {
    Glib::thread_init();
    if(SDL_Init(SDL_INIT_AUDIO)==-1)
        cout << "Error on init sdl library: " << Mix_GetError() << endl;
    Gtk::Main kit(argc, argv);

    curl_global_init(CURL_GLOBAL_ALL);

    DataProcessor::init(argv[0]);
    Log log;
    log.init();

    UI ui;
    ui.init();

    Gtk::Main::run(ui);

    return 0;
}