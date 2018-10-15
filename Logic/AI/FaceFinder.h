#ifndef KOPYTKO_FACEFINDER_H
#define KOPYTKO_FACEFINDER_H

#include <Logic/Misc/Thread.h>
#include <Logic/HWDrivers/Camera.h>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>

#include <DataProcessing/DataProcessor.h>

using namespace std;

class FaceFinder : public Thread  {
public:
    FaceFinder(DataProcessor *dataProcessor);
    vector<dlib::matrix<dlib::rgb_pixel>>* getFaceImgs();
    void getFaceImgs(vector<dlib::matrix<dlib::rgb_pixel>>* faceImgs);
    int getFaceImgsSize();

protected:
    void onStart() override;

    void onRun() override;

    void onStop() override;

private:
    DataProcessor *dataProcessor;
    Camera *camera;
    cv::Mat imgBuff;

    pthread_mutex_t imgsLock;

    dlib::frontal_face_detector face_detector;
    dlib::shape_predictor sp;

    vector<dlib::matrix<dlib::rgb_pixel>> faceImgs;
    vector<dlib::matrix<dlib::rgb_pixel>> faceImgsBuff;
};


#endif //KOPYTKO_FACEFINDER_H
