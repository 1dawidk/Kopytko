#ifndef KOPYTKO_SESSION_H
#define KOPYTKO_SESSION_H

#include <Logic/Misc/Thread.h>
#include <DataProcessing/DataProcessor.h>
#include <UI/User.h>

#define LINE_LABELS_NO      3

class UI;

class Session : public Thread {
public:
    Session(int userId, UI *ui);

    int getUserId();
protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    User *user;

    UI *ui;
};


#endif //KOPYTKO_SESSION_H
