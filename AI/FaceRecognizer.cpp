#include "FaceRecognizer.h"

void FaceRecognizer::stop() {
    runThread= false;
}

void FaceRecognizer::run() {
    cv::Mat imgBuff;
    runThread= true;

    //Init camera
    camera= new Camera();
    camera->init(1024, 1024);

    //Init dlib face detector
    face_detector= dlib::get_frontal_face_detector();
    while (runThread){
        //TEST FACE DETECTION
        std::cout << "Capturing image..." << endl;
        camera->getImage(&imgBuff);
        std::cout << "Done" << endl;
        //cv::imwrite("../../test.jpg", imgBuff);
        std::cout << "Preparing image..." << endl;
        dlib::cv_image<dlib::bgr_pixel> img(imgBuff);
        std::cout << "Done" << endl;
        std::cout << "Looking for faces..." << endl;
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
