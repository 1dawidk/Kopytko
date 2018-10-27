#include <Logic/Misc/Clock.h>
#include <highgui.h>
#include "VoiceRecognizer.h"

void VoiceRecognizer::onStart() {
    soundRecorder= new SoundRecorder(8000, 1);
    spectrumGatherer= new SpectrumGatherer(soundRecorder);

    soundRecorder->start();
    spectrumGatherer->start();

    specBuff= new double[spectrumGatherer->getSpectrumBufferSize()];
}

void VoiceRecognizer::onRun() {
    //spectrumGatherer->getSpectrum(specBuff);
}

void VoiceRecognizer::onStop() {
    cout << "\t\tStop: Spectrum Getherer" << endl;
    spectrumGatherer->stop();
    cout << "\t\tStop: Sound Recorder"  << endl;
    soundRecorder->stop();
    cout << "\t\tClean: Voice Recognizer memory" << endl;

    delete spectrumGatherer;
    delete soundRecorder;
    delete[] specBuff;
}


