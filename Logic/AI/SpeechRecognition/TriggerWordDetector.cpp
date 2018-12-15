#include <dkulpaclibs/misc/debug/Log.h>
#include "TriggerWordDetector.h"

TriggerWordDetector::TriggerWordDetector(SoundRecorder *soundRecorder) {
    this->soundRecorder= soundRecorder;
}

void TriggerWordDetector::onStart() {
    spectrumGatherer= new SpectrumGatherer(soundRecorder);
    spectrumGatherer->start();
    specBuff= new double[spectrumGatherer->getSpectrumBufferSize()];

    found= false;
}

void TriggerWordDetector::onRun() {
    //spectrumGatherer->getSpectrum(specBuff);
}

void TriggerWordDetector::onStop() {
    Log::write("VoiceRecognizer", "Stop: Spectrum Gatherer");
    spectrumGatherer->stop();
    Log::write("VoiceRecognizer", "Stop: Sound Recorder");
    soundRecorder->stop();
    Log::write("VoiceRecognizer", "Clear memory");

    delete spectrumGatherer;
    delete soundRecorder;
    delete[] specBuff;
}
