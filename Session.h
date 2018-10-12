#ifndef KOPYTKO_SESSION_H
#define KOPYTKO_SESSION_H

#include <Logic/Misc/Thread.h>
#include <DataProcessing/DataProcessor.h>

class Session : public Thread {
public:
    Session(int userId, DataProcessor *dataProcessor);

protected:
    void onStart() override;

    void onRun() override;

    void onStop() override;

private:
    int userId;
    int btDeviceId;
    int ihId;
    string userName;

    void readUserData(DataProcessor *dataProcessor);
};


#endif //KOPYTKO_SESSION_H
