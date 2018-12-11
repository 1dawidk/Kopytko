#ifndef KOPYTKO_FACERECOGNIZER_H
#define KOPYTKO_FACERECOGNIZER_H


#include "Logic/Misc/Thread.h"
#include "Logic/HWDrivers/Camera.h"

#include <vector>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#include <UI/UI.h>
#include <Logic/AI/FaceRecognition/FaceModel.h>
#include <Logic/AI/FaceRecognition/FaceFinder.h>

#include <Logic/AI/FaceRecognition/FaceNetTemplate.h>

#define FACE_NO_FACE    -1
#define FACE_UNKNOWN    0

//REQUIRED: dlib, libblas, liblapack, libsqlite-3

using namespace std;

class FaceRecognizer : public Thread {
public:
    FaceRecognizer(UI *ui);

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    UI *ui;
    DataProcessor *dataProcessor;

    Camera *camera;
    cv::Mat imgBuff;

    dlib::frontal_face_detector face_detector;
    dlib::shape_predictor sp;
    anet_type net;

    vector<FaceModel*> faceModels;
};


#endif //KOPYTKO_FACERECOGNIZER_H
