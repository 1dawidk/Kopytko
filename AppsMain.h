#ifndef KOPYTKO_APPSMAIN_H
#define KOPYTKO_APPSMAIN_H

#include <UI/MainContext.h>
#include <Logic/AI/FaceRecognizer.h>
#include <DataProcessing/DataProcessor.h>

#include <Logic/Misc/Thread.h>

class AppsMain : public Thread {
public:
    AppsMain(int argc, char *argv[]);

    void run();

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    MainContext *ui;
    DataProcessor *dataProcessor;
    FaceRecognizer *faceRecognizer;

    int argc;
    char *argv[];
};


#endif //KOPYTKO_APPSMAIN_H
