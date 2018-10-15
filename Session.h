#ifndef KOPYTKO_SESSION_H
#define KOPYTKO_SESSION_H

#include <Logic/Misc/Thread.h>
#include <DataProcessing/DataProcessor.h>

#define LINE_LABELS_NO      3

class UI;

class Session : public Thread {
public:
    Session(int userId, DataProcessor *dataProcessor, UI *ui);

    int getUserId();

    static int getLineLabelId(string &line);
    static string getLineLabel(string &line);
    static string getLineValue(string &line);
protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    int userId;
    int btDeviceId;
    int ihId;
    string userName;

    UI *ui;

    void readUserData(DataProcessor *dataProcessor);

    static string idToLabel[LINE_LABELS_NO];
};


#endif //KOPYTKO_SESSION_H
