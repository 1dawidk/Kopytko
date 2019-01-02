#include <dkulpaclibs/misc/debug/Log.h>
#include "PhoneConnectionManager.h"

void PhoneConnectionManager::onStart() {
    // Start bluetooth manager
    btManager= new BluetoothManager();
    btManager->start();
}

void PhoneConnectionManager::onRun() {


    if(btManager->isCliConnected()) {
        syncStep(); //Sync process state machine handling
    } else {
        syncState = PCM_SYNC_STATE_IDLE;
    }


    //Determine for how long pause tread execution
    if(syncState==PCM_SYNC_STATE_SYNCED || syncState==PCM_SYNC_STATE_FAILED || syncState==PCM_SYNC_STATE_IDLE){
        Thread::pause(1000);
    } else {
        Thread::pause(100);
    }

}

void PhoneConnectionManager::syncStep() {

        // ###### IDLE STATE ######
    if(syncState==PCM_SYNC_STATE_IDLE) {
        Log::write("PhoneConnectionManager", "Start sync sequence...");
        btManager->write("start_sync\n");
        syncState=PCM_SYNC_STATE_STARTED;
    }

        // ###### STARTED STATE ######
    else if(syncState==PCM_SYNC_STATE_STARTED){
        if(btManager->read()=="sync_began") {
            syncState = PCM_SYNC_STATE_WORKING;
            Log::write("PhoneConnectionManager", "Sync working!");
            syncStartTime= Clock::GetTimeMs();
            lastSyncState= PCM_SYNC_STATE_STARTED;
        }
    }

        // ###### WORKING STATE ######
    else if(syncState==PCM_SYNC_STATE_WORKING){
        //Check if sync timeout
        if(Clock::GetTimeMs()-syncStartTime>PCM_TIMEOUT_VALUE){
            //If true set failed state
            syncState=PCM_SYNC_STATE_FAILED;
            btManager->write("timeout");
            syncStartTime= Clock::GetTimeMs();
            Log::write("PhoneConnectionManager", "Sync timeout");
        } else {
            //If not read notif data
            string rxData = btManager->read();
            if (!rxData.empty()) {
                if (rxData == "sync_end") {
                    syncState = PCM_SYNC_STATE_SYNCED;
                    Log::write("PhoneConnectionManager", "Sync acquired");
                    lastSyncState = PCM_SYNC_STATE_WORKING;
                } else {
                    PhoneNotification *pn = PhoneNotification::newInstance(rxData);
                    if (pn != NULL) {
                        notifs.push_back(pn);
                        Log::write("PhoneConnectionManager", "New phone notification");
                    }
                }
            }
        }
    }

        // ###### FAILED STATE ######
    else if(syncState==PCM_SYNC_STATE_FAILED){
        if(Clock::GetTimeMs()-syncStartTime>PCM_TIMEOUT_VALUE){

        }
    }

        // ###### SYNCED STATE ######
    else if(syncState==PCM_SYNC_STATE_SYNCED){
    }
}

void PhoneConnectionManager::onStop() {
    btManager->stop();
}

void PhoneConnectionManager::start() {
    Thread::start();
}
