#include <Logic/Misc/Clock.h>
#include <Debug/Log.h>
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
    Log::write("VoiceRecognizer", "Stop: Spectrum Gatherer");
    spectrumGatherer->stop();
    Log::write("VoiceRecognizer", "Stop: Sound Recorder");
    soundRecorder->stop();
    Log::write("VoiceRecognizer", "Clear memory");

    delete spectrumGatherer;
    delete soundRecorder;
    delete[] specBuff;
}


