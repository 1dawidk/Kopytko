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
    camera->init(512, 512);



    //Init dlib face detector
    face_detector= dlib::get_frontal_face_detector();
    while (runThread){
        //TEST FACE DETECTION
        camera->getImage(&imgBuff); //Get camera image
        dlib::cv_image<dlib::bgr_pixel> img(imgBuff);

        std::vector<dlib::rectangle> faces=face_detector(img);
        if(!faces.empty()) {
            cv::Rect faceRect;
            faceRect.x= (int)faces[0].left();
            faceRect.y= (int)faces[0].top();
            faceRect.height= (int)(faces[0].right()-faces[0].left());
            faceRect.width= (int)(faces[0].bottom()-faces[0].top());
            context->onFaceDetected(0);
            cv::rectangle(imgBuff, faceRect, cvScalar(255, 0, 0), 2);

        }

        context->showImage(imgBuff);
        //###################
    }
}
