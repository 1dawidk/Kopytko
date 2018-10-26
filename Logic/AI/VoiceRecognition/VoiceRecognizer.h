#ifndef KOPYTKO_VOICERECOGNIZER_H
#define KOPYTKO_VOICERECOGNIZER_H

#include <Logic/Misc/Thread.h>
#include <Logic/HWDrivers/SoundRecorder.h>
#include <Logic/AI/VoiceRecognition/SpectrumGatherer.h>
#include <fftw3.h>
#include <math.h>


class VoiceRecognizer : public Thread {
protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    SoundRecorder *soundRecorder;
    SpectrumGatherer *spectrumGatherer;

    double *specBuff;
};


#endif //KOPYTKO_VOICERECOGNIZER_H
