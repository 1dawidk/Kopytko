#include <DataProcessing/DataProcessor.h>
#include <dkulpaclibs/misc/debug/Log.h>
#include "User.h"

string User::idToLabel[LINE_LABELS_NO]={
        "Name",
        "DeviceId",
        "HomeId"
};

User::User(int userId) {
    this->id= userId;

    string line;
    ifstream file= DataProcessor::openReadFile("/data/users/user"+to_string(userId), OPEN_FILE_MODE_RELATIVE);

    if(file.is_open()) {
        while (getline(file, line)) {
            int labelId= getLineLabelId(line);
            string value= getLineValue(line);

            size_t spacePos;

            switch (labelId){
                case 0:
                    spacePos= value.find_first_of(' ');
                    name= line.substr(0, spacePos);
                    sname= line.substr(spacePos+1);
                    break;
                case 1:
                    deviceId= stol(value);
                    break;
                case 2:
                    homeId= stol(value);
                    break;
            }
        }

        file.close();
        Log::write("User", "New user: %s %s, homeId: %ld, phoneId: %ld", name.c_str(), sname.c_str(), homeId, deviceId);
    } else {
        Log::write("User", "Error creating new user");
    }


}

int User::getLineLabelId(string &line) {
    string label= getLineLabel(line);

    for(int i=0; i<LINE_LABELS_NO; i++){
        if(idToLabel[i]==label)
            return i;
    }

    return -1;
}

string User::getLineLabel(string &line) {
    size_t semiPos= line.find_first_of(':');
    return line.substr(0, semiPos);
}

string User::getLineValue(string &line) {
    size_t semiPos= line.find_first_of(':');
    return line.substr(semiPos+2);
}

int User::getId() {
    return id;
}

string User::getName() {
    return name;
}

long User::getDeviceId() {
    return deviceId;
}

long User::getHomeId() {
    return homeId;
}
