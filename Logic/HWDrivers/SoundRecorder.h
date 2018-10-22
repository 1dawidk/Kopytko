#ifndef KOPYTKO_SOUNDRECORDER_H
#define KOPYTKO_SOUNDRECORDER_H

#include <Logic/Misc/Thread.h>
#include <iostream>
#include <alsa/asoundlib.h>
#include <fstream>

using namespace std;

class SoundRecorder : public Thread {
public:

    SoundRecorder(size_t buffSize, int chNo);
    int getRecording(char* buff, size_t *len);
    char* createBuff();

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    int chNo;               //Nuber of channels
    char *buffer;           //Byte array
    snd_pcm_format_t format;

    size_t buffHead;        //Byte pointer
    size_t realBuffSize;    //Bytes in buffer
    size_t buffSize;        //Readings per channel

    int overflowFlag;       //Buffer overflow flag (1 - overflow occurred)

    snd_pcm_t *capture_handle;

    pthread_mutex_t buffM;
};


#endif //KOPYTKO_SOUNDRECORDER_H