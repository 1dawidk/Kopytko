#ifndef KOPYTKO_SESSION_H
#define KOPYTKO_SESSION_H

#include <dkulpaclibs/misc/Thread.h>
#include <DataProcessing/DataProcessor.h>
#include <UI/User.h>
#include <string>

#define SESSION_IDLE_MAX_DURATION_S 0

using namespace std;

class UI;

class Session : public Thread {
public:
    Session(int userId, UI *ui);

    void refresh();

    int getUserId();
    long getUpTime();
    string getUserName();
protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    User *user;

    long startTime;

    UI *ui;
};


#endif //KOPYTKO_SESSION_H
