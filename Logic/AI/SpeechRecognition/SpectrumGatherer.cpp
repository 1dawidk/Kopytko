#include "SpectrumGatherer.h"
#include <highgui.h>

SpectrumGatherer::SpectrumGatherer(SoundRecorder *soundRecorder) {
    this->soundRecorder= soundRecorder;
    spectrumMutex=PTHREAD_MUTEX_INITIALIZER;
    spectrumBuffLen=0;
}

void SpectrumGatherer::getSpectrum(double *buff) {
    pthread_mutex_lock(&spectrumMutex);
    memcpy(buff, spectrum+spectrumHead, sizeof(double)*(spectrumBuffLen-spectrumHead));
    memcpy(buff+(spectrumBuffLen-spectrumHead), spectrum, sizeof(double)*spectrumHead);
    pthread_mutex_unlock(&spectrumMutex);
}

size_t SpectrumGatherer::getSpectrumBufferSize() {
    return spectrumBuffLen;
}

void SpectrumGatherer::onStart() {
    sBuff= new float[soundRecorder->getFrameBuffSize()];
    sBuffHead=0;

    fftOut= new fftwf_complex[320];
    spectrumBuffLen=320*100;
    spectrum= new double[spectrumBuffLen]; //320 samples per 20ms -> 1s = 50 * 20ms -> 100 / 50 = 2s
    spectrumHead=0;

    pl = fftwf_plan_dft_r2c_1d(320, sBuff, fftOut, FFTW_MEASURE);

    img= new cv::Mat(100, 160, CV_8UC3);
}

void SpectrumGatherer::onRun() {
    size_t readLen;

    soundRecorder->getRecording((char*)(sBuff+sBuffHead), &readLen);
    readLen+=sBuffHead; //Inc read length by samples left from previous cycle

    //Check if there is enough samples
    if(readLen<320){
        sBuffHead=readLen;
    } else {
        sBuffHead=0;

        int n = (int) readLen / 320;
        for (int i = 0; i < n; i++) {

            //Execute FFT
            fftwf_execute_dft_r2c(pl, sBuff+(320*i), fftOut);

            //Convert FFT output to spectrum freq samples amplitude
            pthread_mutex_lock(&spectrumMutex);
            for(int j=0; j<161; j++){
                double amp= fftOut[j][0]*fftOut[j][0] + fftOut[j][1]*fftOut[j][1];
                spectrum[spectrumHead+j]=sqrt(amp);
            }

            drawSpectrum(img);
            //Move spectrum end pointer by 320 values
            spectrumHead += 320;
            pthread_mutex_unlock(&spectrumMutex);

            //If spectrum end has reached spectrum buff size -> cycle
            if (spectrumHead >= 320 * 100) {
                spectrumHead = 0;
            }
        }

        //Move unused samples to the beginning of sound buffer
        sBuffHead= readLen - (320*n);
        memcpy(sBuff, sBuff+(n*320), sBuffHead*4);
    }

}

void SpectrumGatherer::onStop() {
    delete[] sBuff;
    fftwf_destroy_plan(pl);
    fftwf_free(spectrum);
}

#define SPEC_MAX    35.0

void SpectrumGatherer::drawSpectrum(cv::Mat *img) {
    for(int i=0; i<161; i++){
        double amp= spectrum[spectrumHead+i];
        int line= spectrumHead/320;

        uchar r;
        uchar g;
        uchar b;

        if(amp<SPEC_MAX*0.1){
            b=255;
            g=(255/(SPEC_MAX/10))*amp;
            r=0;

        } else if(amp<SPEC_MAX*0.3){
            b=(-255/(SPEC_MAX/5))*amp+382.5;
            g=255;
            r=0;

        } else if(amp<SPEC_MAX*0.6){
            b=0;
            g=255;
            r=(1275/(SPEC_MAX*3))*amp-255;

        } else if(amp<SPEC_MAX) {
            b=0;
            g=(-1275/(SPEC_MAX*4))*amp+637,5;
            r=255;

        } else {
            b=0;
            g=0;
            r=255;
        }

        img->at<cv::Vec3b>(line,i)[0] = b;
        img->at<cv::Vec3b>(line,i)[1] = g;
        img->at<cv::Vec3b>(line,i)[2] = r;
    }
}
