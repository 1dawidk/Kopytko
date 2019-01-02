#ifndef KOPYTKO_PHONENOTIFICATION_H
#define KOPYTKO_PHONENOTIFICATION_H

#include <string>
#include <dkulpaclibs/misc/PostPairs.h>
#include <Logic/Notification.h>

using namespace std;

class PhoneNotification : public Notification {
public:
    static PhoneNotification* newInstance(string postPairs);

    string getAppName();
    string getTitle() override;

private:
    string appName;
};


#endif //KOPYTKO_PHONENOTIFICATION_H
