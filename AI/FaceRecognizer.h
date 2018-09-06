#ifndef KOPYTKO_FACERECOGNIZER_H
#define KOPYTKO_FACERECOGNIZER_H


#include "../Misc/Thread.h"
#include "../HWDrivers/Camera.h"

#include <vector>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <UI/AppMainWindow.h>

//REQUIRED: dlib, libblas, liblapack, libsqlite-3

using namespace std;

class FaceRecognizer : public Thread {
public:
    FaceRecognizer(AppMainWindow *context);
    void stop() override;
    dlib::frontal_face_detector face_detector;

protected:
    void run() override;

private:
    Camera *camera;
    AppMainWindow *context;
};


#endif //KOPYTKO_FACERECOGNIZER_H
