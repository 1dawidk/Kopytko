#ifndef KOPYTKO_PHONECONNECTIONMANAGER_H
#define KOPYTKO_PHONECONNECTIONMANAGER_H


#include <dkulpaclibs/misc/Thread.h>

class PhoneConnectionManager : Thread {
public:
    void start() override;

private:
    void onStart() override;
    void onRun() override;
    void onStop() override;
};


#endif //KOPYTKO_PHONECONNECTIONMANAGER_H
