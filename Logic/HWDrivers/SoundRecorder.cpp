#include "SoundRecorder.h"

SoundRecorder::SoundRecorder(size_t frameBuffSize, int chNo) {
    this->frameBuffSize= frameBuffSize;
    this->chNo= chNo;
    buffM= PTHREAD_MUTEX_INITIALIZER;
}

int SoundRecorder::getRecording(char *buff, size_t *len) {
    int flag= overflowFlag;

    pthread_mutex_lock(&buffM);
    memcpy(buff, buffer, buffHead);
    *len= buffHead / (snd_pcm_format_width(format)/8);
    buffHead=0;
    overflowFlag=0;
    pthread_mutex_unlock(&buffM);

    return flag;
}

size_t SoundRecorder::getFrameBuffSize() {
    return frameBuffSize;
}


void SoundRecorder::onStart() {
    unsigned int rate = 16000;

    snd_pcm_hw_params_t *hw_params;
    format = SND_PCM_FORMAT_FLOAT_LE;

    //Open audio interface
    if( snd_pcm_open(&capture_handle, "plughw:1,0", SND_PCM_STREAM_CAPTURE, SND_PCM_NONBLOCK) < 0 ) {
        cout << "Kopytko ERROR: cannot open audio interface" << endl;
        this->stop();
        return;
    }

    //Alloc hardware params
    if( snd_pcm_hw_params_malloc (&hw_params) < 0 ) {
        cout << "Kopytko ERROR: cannot alloc hw params" << endl;
        this->stop();
        return;
    }

    //Initialize hardware params obj
    if(snd_pcm_hw_params_any (capture_handle, hw_params) < 0) {
        cout << "Kopytko ERROR: cannot initialize hw params obj" << endl;
        this->stop();
        return;
    }


    if(snd_pcm_hw_params_set_rate_resample(capture_handle, hw_params, 1)<0){
        cout << "Kopytko ERROR: cannot enable resampling" << endl;
        this->stop();
        return;
    }

    snd_pcm_uframes_t frames=2048;
    int dir;
    snd_pcm_hw_params_set_period_size_near(capture_handle, hw_params, &frames, &dir);

    cout << "Dir " << dir;


    unsigned int re;
    snd_pcm_hw_params_get_rate_resample(capture_handle, hw_params,&re);
    cout << "Resample state: " << to_string(re) << endl;

    //Set access type
        if(snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
        cout << "Kopytko ERROR: cannot set access type" << endl;
        this->stop();
        return;
    }

    //Set format type
    if(snd_pcm_hw_params_set_format (capture_handle, hw_params, format) < 0) {
        cout << "Kopytko ERROR: cannot set format type" << endl;
        this->stop();
        return;
    }

    //Set sample rate
    if(snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &rate, 0) < 0) {
        cout << "Kopytko ERROR: cannot set sample rate" << endl;
        this->stop();
        return;
    }

    cout << "Audio sample rate: " << to_string(rate) << "Hz" << endl;

    //Set channel count
    if (snd_pcm_hw_params_set_channels (capture_handle, hw_params, chNo) < 0) {
        cout << "Kopytko ERROR: cannot set channel count" << endl;
        this->stop();
        return;
    }

    //Finally set hardware params
    if (snd_pcm_hw_params (capture_handle, hw_params) < 0) {
        cout << "Kopytko ERROR: cannot set hw params" << endl;
        this->stop();
        return;
    }


    snd_pcm_hw_params_free (hw_params);

    if (snd_pcm_prepare (capture_handle) < 0) {
        cout << "Kopytko ERROR: cannon prepare audio interface" << endl;
    }

    byteBuffSize= frameBuffSize * (snd_pcm_format_width(format)/8) * chNo;
    buffer = (char*)malloc(byteBuffSize);
    buffHead=0;

    cout << "Format width: " << snd_pcm_format_width(format) << endl;

}

void SoundRecorder::onRun() {
    long fr;

    pthread_mutex_lock(&buffM);
    if( (fr=snd_pcm_readi(capture_handle, buffer+buffHead, 128)) > 0) {
        buffHead += fr*(snd_pcm_format_width(format)/8);
    } else {
    }

    if(buffHead>=byteBuffSize) {
        buffHead = 0;
        overflowFlag=1;
    }
    pthread_mutex_unlock(&buffM);
}

void SoundRecorder::onStop() {
    free(buffer);
    snd_pcm_close (capture_handle);
}
