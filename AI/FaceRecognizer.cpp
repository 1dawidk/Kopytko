#include "FaceRecognizer.h"

void FaceRecognizer::stop() {
    runThread= false;
}

void FaceRecognizer::run() {
    cv::Mat imgBuff;
    runThread= true;

    //Init camera
    camera= new Camera();
    //camera->init(1024, 1024);

    //Init dlib face detector
    face_detector= dlib::get_frontal_face_detector();
    while (runThread){
        //TEST FACE DETECTION
        camera->getImage(&imgBuff);
        //cv::imwrite("../../test.jpg", imgBuff);
        dlib::cv_image<dlib::bgr_pixel> img(imgBuff);
        std::vector<dlib::rectangle> faces=face_detector(img);
        //###################

        std::cout << faces.size() << " faces detected" << endl;
    }
}

void FaceRecognizer::detectFace(uint8_t *buf) {
    //dlib::cv_image<dlib::bgr_pixel> cimg(*buf);

    //std::vector<dlib::rectangle> faces;
    //faces= face_detector(cimg);
    //cout << faces.size() << endl;
}
