#ifndef KOPYTKO_PHONECONNECTIONMANAGER_H
#define KOPYTKO_PHONECONNECTIONMANAGER_H


#include <dkulpaclibs/misc/Thread.h>
#include <dkulpaclibs/hw/bluetooth/BluetoothManager.h>

class PhoneConnectionManager : public Thread {
public:
    void start() override;

private:
    void onStart() override;
    void onRun() override;
    void onStop() override;

    BluetoothManager *btManager;
};


#endif //KOPYTKO_PHONECONNECTIONMANAGER_H
