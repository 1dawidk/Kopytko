#ifndef KOPYTKO_VOICERECOGNIZER_H
#define KOPYTKO_VOICERECOGNIZER_H

#include <dkulpaclibs/misc/Thread.h>
#include <dkulpaclibs/hw/SoundRecorder.h>
#include <Logic/AI/SpeechRecognition/SpectrumGatherer.h>
#include <Logic/AI/SpeechRecognition/TriggerWordDetector.h>
#include <fftw3.h>
#include <math.h>


class VoiceRecognizer : public Thread {
protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    TriggerWordDetector *triggerWordDetector;
    SoundRecorder *soundRecorder;
    SpectrumGatherer *spectrumGatherer;
};


#endif //KOPYTKO_VOICERECOGNIZER_H
