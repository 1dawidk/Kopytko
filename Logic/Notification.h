#ifndef KOPYTKO_NOTIFICATION_H
#define KOPYTKO_NOTIFICATION_H

#include <string>

using namespace std;

#define NOTIFICATION_FROM_PHONE  0
#define NOTIFICATION_FROM_HOME   1
#define NOTIFICATION_FROM_MIRROR 2

class Notification {
public:
    int getFrom();
    virtual string getTitle();
    string getText();

protected:
    int from;
    string title;
    string text;


};


#endif //KOPYTKO_NOTIFICATION_H
