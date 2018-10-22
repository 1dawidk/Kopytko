#include "VoiceRecognizer.h"

void VoiceRecognizer::onStart() {
    soundRecorder= new SoundRecorder(4000, 1);
    soundRecorder->start();

    soundHead=0;
    sBuff= new int16_t[4000];
    //sBuff= soundRecorder->createBuff();

    soundPart= new double[320];
    soundSpectrum= new double[320*100];  //320 per 20ms -> 50 * 20ms = 1s -> 250 / 50 = 5s
}

void VoiceRecognizer::onRun() {
    size_t readLen;
    int overflowFlag;

    overflowFlag=soundRecorder->getRecording((char*)sBuff, &readLen);

    for(int i=0; i<readLen/320; i++){


        //p= fftw_plan_dft_r2c_1d(320, soundPart, out)
    }

    //p= fftw_plan_dft_r2c_1d(320, sound, out, FFTW_MEASURE);

}

void VoiceRecognizer::onStop() {

}
