#ifndef KOPYTKO_TRIGGERWORDDETECTOR_H
#define KOPYTKO_TRIGGERWORDDETECTOR_H


#include <dkulpaclibs/misc/Thread.h>
#include "SpectrumGatherer.h"

class TriggerWordDetector : Thread {
public:
    TriggerWordDetector(SoundRecorder *soundRecorder);

private:
    SoundRecorder *soundRecorder;
    SpectrumGatherer *spectrumGatherer;
    double *specBuff;
    bool found;

    void onStart() override;
    void onRun() override;
    void onStop() override;
};


#endif //KOPYTKO_TRIGGERWORDDETECTOR_H
