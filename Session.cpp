#include "Session.h"
#include <UI/UI.h>

string Session::idToLabel[LINE_LABELS_NO]={
        "Name",
        "DeviceId",
        "HomeId"
};

Session::Session(int userId, DataProcessor *dataProcessor, UI *ui) {
    this->userId= userId;
    this->ui= ui;
    readUserData(dataProcessor);
}

int Session::getUserId() {
    return userId;
}

void Session::readUserData(DataProcessor *dataProcessor) {
    string line;
    ifstream file= dataProcessor->openReadFile("/data/users/user"+to_string(userId), OPEN_FILE_MODE_RELATIVE);

    if(file.is_open()) {
        while (getline(file, line)) {
            int labelId= getLineLabelId(line);
            string value= getLineValue(line);

            cout << "Label ID: " << labelId << " with value: " << value;
        }
    }
}

int Session::getLineLabelId(string &line) {
    string label= getLineLabel(line);

    for(int i=0; i<LINE_LABELS_NO; i++){
        if(idToLabel[i]==label)
            return i;
    }

    return -1;
}

string Session::getLineLabel(string &line) {
    size_t semiPos= line.find_first_of(':');
    return line.substr(0, semiPos);
}

string Session::getLineValue(string &line) {
    size_t semiPos= line.find_first_of(':');
    return line.substr(semiPos+2);
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
