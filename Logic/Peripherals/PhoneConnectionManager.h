#ifndef KOPYTKO_PHONECONNECTIONMANAGER_H
#define KOPYTKO_PHONECONNECTIONMANAGER_H


#include <dkulpaclibs/misc/Thread.h>
#include <dkulpaclibs/hw/bluetooth/BluetoothManager.h>
#include <Logic/PhoneNotification.h>

#define PCM_SYNC_STATE_IDLE         0
#define PCM_SYNC_STATE_STARTED      1
#define PCM_SYNC_STATE_WORKING      2
#define PCM_SYNC_STATE_FAILED       3
#define PCM_SYNC_STATE_SYNCED       4

#define PCM_TIMEOUT_VALUE           2000

class PhoneConnectionManager : public Thread {
public:
    void start() override;

private:
    void onStart() override;
    void onRun() override;
    void onStop() override;

    void syncStep();

    BluetoothManager *btManager;
    vector<PhoneNotification*> notifs;

    int lastSyncState;
    int syncState;
    long syncStartTime;
};


#endif //KOPYTKO_PHONECONNECTIONMANAGER_H
