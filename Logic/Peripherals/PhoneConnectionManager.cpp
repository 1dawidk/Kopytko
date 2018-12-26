#include <dkulpaclibs/misc/debug/Log.h>
#include "PhoneConnectionManager.h"

void PhoneConnectionManager::onStart() {
    btManager= new BluetoothManager();
    btManager->start();
}

void PhoneConnectionManager::onRun() {
    if(btManager->isCliConnected()) {
        btManager->write("test_msg\n");
        Log::write("PhoneConMgr", "Send test message");
    }
    Thread::pause(1000);
}

void PhoneConnectionManager::onStop() {
    btManager->stop();
}

void PhoneConnectionManager::start() {
    Thread::start();
}
