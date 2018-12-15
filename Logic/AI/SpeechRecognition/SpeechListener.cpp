#include <dkulpaclibs/misc/Clock.h>
#include <dkulpaclibs/misc/debug/Log.h>
#include <highgui.h>
#include "SpeechListener.h"

void VoiceRecognizer::onStart() {
    soundRecorder= new SoundRecorder(8000, 1);
    soundRecorder->start();

    triggerWordDetector= new TriggerWordDetector(soundRecorder);
}

void VoiceRecognizer::onRun() {

}

void VoiceRecognizer::onStop() {

}


