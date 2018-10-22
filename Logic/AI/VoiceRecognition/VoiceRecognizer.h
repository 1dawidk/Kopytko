#ifndef KOPYTKO_VOICERECOGNIZER_H
#define KOPYTKO_VOICERECOGNIZER_H

#include <Logic/Misc/Thread.h>
#include <Logic/HWDrivers/SoundRecorder.h>
#include <fftw3.h>

class VoiceRecognizer : public Thread {
protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    SoundRecorder *soundRecorder;

    int16_t* sBuff;

    double* soundPart;
    size_t  soundHead;
    size_t  soundLen;

    double* soundSpectrum;

    fftw_complex *out;
    fftw_plan p;
};


#endif //KOPYTKO_VOICERECOGNIZER_H
