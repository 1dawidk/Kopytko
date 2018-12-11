#include "Session.h"
#include <UI/UI.h>

Session::Session(int userId, UI *ui) {
    this->ui= ui;

    user= new User(userId);
}

int Session::getUserId() {
    return 0;
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
    //Clear user layout
}
