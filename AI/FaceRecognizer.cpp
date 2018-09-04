#include "FaceRecognizer.h"

void FaceRecognizer::stop() {
    runThread= false;
}

void FaceRecognizer::run() {
    //cv::Mat imgBuff;
    runThread= true;

    //Init camera
    //camera= new Camera();
    //camera->init(1024, 1024);

    //Init dlib face detector
    //face_detector= dlib::get_frontal_face_detector();

    //TEST FACE DETECTION
    //takePhoto(&imgBuff);
    //detectFace(&imgBuff);
    //###################

    while (runThread){

    }
}

void FaceRecognizer::takePhoto(uint8_t *buf) {
}

void FaceRecognizer::detectFace(uint8_t *buf) {
    //dlib::cv_image<dlib::bgr_pixel> cimg(*buf);

    //std::vector<dlib::rectangle> faces;
    //faces= face_detector(cimg);
    //cout << faces.size() << endl;
}
