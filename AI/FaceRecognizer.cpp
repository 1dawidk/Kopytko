#include "FaceRecognizer.h"

FaceRecognizer::FaceRecognizer(AppMainWindow *context){
    this->context= context;
}

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
        context->showImage(imgBuff);
        std::cout << "Looking for faces..." << endl;
        std::vector<dlib::rectangle> faces=face_detector(img);
        //###################

        std::cout << faces.size() << " faces detected" << endl;
    }
}
