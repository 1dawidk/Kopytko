#include "Session.h"

Session::Session(int userId, DataProcessor *dataProcessor) {
    this->userId= userId;
    readUserData(dataProcessor);
}

void Session::readUserData(DataProcessor *dataProcessor) {

}

void Session::onStart() {

}

void Session::onRun() {

}

void Session::onStop() {

}
