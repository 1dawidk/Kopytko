#include "AppsMain.h"

AppsMain::AppsMain(int argc, char **argv) {

}

void AppsMain::run() {
    this->ui= new MainContext(argv[0]);
    this->faceRecognizer= new FaceRecognizer(ui);
}

void AppsMain::onStop() {

}

void AppsMain::onRun() {

}

void AppsMain::onStart() {

}
