#ifndef KOPYTKO_HOMECONNECTIONMANAGER_H
#define KOPYTKO_HOMECONNECTIONMANAGER_H


#include <dkulpaclibs/misc/Thread.h>

class HomeConnectionManager : Thread {

private:
    void onStart() override;
    void onRun() override;
    void onStop() override;
};


#endif //KOPYTKO_HOMECONNECTIONMANAGER_H
