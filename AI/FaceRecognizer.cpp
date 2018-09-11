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
        std::cout << "Get camera image..." << endl;
        camera->getImage(&imgBuff); //Get camera image
        std::cout << "Get camera image [ Done ]" << endl;
        dlib::cv_image<dlib::bgr_pixel> img(imgBuff); //
        std::cout << "Show image..." << endl;
        context->showImage(imgBuff);
        std::cout << "Show image [ Done ]" << endl;
        std::vector<dlib::rectangle> faces=face_detector(img);
        if(faces.size()>0)
            context->onFaceDetected(0);
        //###################

        std::cout << faces.size() << " faces detected" << endl;
    }
}
