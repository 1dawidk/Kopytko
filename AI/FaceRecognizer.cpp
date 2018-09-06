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
        camera->getImage(&imgBuff); //Get camera image
        dlib::cv_image<dlib::bgr_pixel> img(imgBuff); //
        context->showImage(imgBuff);
        std::vector<dlib::rectangle> faces=face_detector(img);
        //###################

        std::cout << faces.size() << " faces detected" << endl;
    }
}
