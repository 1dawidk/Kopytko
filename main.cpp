#include <iostream>
#include "UI/AppMain.h"
#include "HWDrivers/Camera.h"
#include "AI/FaceRecognizer.h"


int main() {

    //CAMERA TEST!!!!!
    //Camera camera;

    //camera.init(1024, 1024);
    //uint8_t *buff= camera.createBuf();
    //camera.getImage(buff);
    //!!!!!!!!!!!!!!!!

    FaceRecognizer faceRecognizer;
    faceRecognizer.start();


    auto app= AppMain::create("Kopytko");

    return app->run(*app->getMainWindow());
}