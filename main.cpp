#include <iostream>
#include "HWDrivers/Camera.h"
#include "AI/FaceRecognizer.h"
#include <gtkmm.h>
#include "UI/AppMainWindow.h"


int main(int argc, char *argv[]) {

    //CAMERA TEST!!!!!
    //Camera camera;

    //camera.init(1024, 1024);
    //uint8_t *buff= camera.createBuf();
    //camera.getImage(buff);
    //!!!!!!!!!!!!!!!!

    FaceRecognizer faceRecognizer;
    faceRecognizer.start();

    //Gtk::Main kit(argc, argv);

    //AppMainWindow appMainWindow;
    //appMainWindow.init();

    //Gtk::Main::run(appMainWindow);
    while(1);

    return 0;
}