#ifndef KOPYTKO_USER_H
#define KOPYTKO_USER_H

#include <string>

using namespace std;

#define LINE_LABELS_NO      3

class User {
public:
    User(int userId);

    int getId();
    string getName();
    long getDeviceId();
    long getHomeId();
private:
    int id;
    string name;
    string sname;
    long deviceId;
    long homeId;

    static int getLineLabelId(string &line);
    static string getLineLabel(string &line);
    static string getLineValue(string &line);

    static string idToLabel[LINE_LABELS_NO];

};


#endif //KOPYTKO_USER_H
