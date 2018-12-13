#include "Session.h"
#include <UI/UI.h>

Session::Session(int userId, UI *ui) {
    this->ui= ui;

    user= new User(userId);

    startTime= Clock::GetTimeS();
}

int Session::getUserId() {
    return user->getId();
}

void Session::refresh() {
    startTime= Clock::GetTimeS();
}

string Session::getUserName() {
    return user->getName();
}

long Session::getUpTime() {
    return Clock::GetTimeS()-startTime;
}

void Session::onStart() {
    //Prepare user layout

    ui->setLeftViewCallback();
    ui->setMiddleViewCallback();
    ui->setRightViewCallback();
}

void Session::onRun() {
    //While user is in sight run this loop
    //If user is gone check how long is gone
    //If other user in sight hide temp user layout (unless other user is trusted)
}

void Session::onStop() {
    delete user;
    //Clear user layout
}
