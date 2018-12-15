#ifndef KOPYTKO_SPECTRUMGATHERER_H
#define KOPYTKO_SPECTRUMGATHERER_H


#include <dkulpaclibs/misc/Thread.h>
#include <dkulpaclibs/hw/SoundRecorder.h>
#include <dkulpaclibs/misc/Clock.h>
#include <fftw3.h>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <cv.h>

class SpectrumGatherer : public Thread{
public:
    explicit SpectrumGatherer(SoundRecorder *soundRecorder);
    void getSpectrum(double *buff);
    size_t getSpectrumBufferSize();

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    SoundRecorder *soundRecorder;

    float* sBuff;
    size_t sBuffHead;

    fftwf_complex *fftOut;
    double *spectrum;
    size_t spectrumHead;
    size_t spectrumBuffLen;

    fftwf_plan pl;

    pthread_mutex_t spectrumMutex;

    long t;

    cv::Mat *img;
    void drawSpectrum(cv::Mat *img);
};


#endif //KOPYTKO_SPECTRUMGATHERER_H
