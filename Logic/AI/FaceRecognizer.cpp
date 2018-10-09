#include "FaceRecognizer.h"




FaceRecognizer::FaceRecognizer(Context *context){
    this->context= context;
}


void FaceRecognizer::onStart() {
//Init camera
    camera= new Camera();
    camera->init(512, 512);

    //Init dlib face detector
    face_detector= dlib::get_frontal_face_detector();
    dlib::deserialize(context->getRealPath("/data/ai_models/shape_predictor_5_face_landmarks.dat")) >> sp;
    dlib::deserialize(context->getRealPath("/data/ai_models/dlib_face_recognition_resnet_model_v1.dat")) >> net;

    //Load face models
    FaceModel::readModelsFile(context, faceModels, "known_faces");

    ((MainContext *) context)->onFaceDetected("");
}

void FaceRecognizer::onRun() {
    //Get camera image
    camera->getImage(&imgBuff);
    //Convert to dlib/opencv image
    dlib::cv_image<dlib::bgr_pixel> tmp(imgBuff);
    dlib::matrix<dlib::rgb_pixel> img;
    dlib::assign_image(img, tmp);
    //Search for faces
    std::vector<dlib::rectangle> faces=face_detector(img);

    std::vector<dlib::matrix<dlib::rgb_pixel>> faceImgs;

    //Extract each face as 150x150px image
    for(int i=0; i<faces.size(); i++){
        auto shape= sp(img, faces[i]);
        dlib::matrix<dlib::rgb_pixel> face_chip;
        dlib::extract_image_chip(img, dlib::get_face_chip_details(shape, 150, 0.25), face_chip);
        faceImgs.push_back(move(face_chip));
    }


    if(!faceImgs.empty()) {
        // This call asks the DNN to convert each face image in faces into a 128D vector.
        // In this 128D vector space, images from the same person will be close to each other
        // but vectors from different people will be far apart.  So we can use these vectors to
        // identify if a pair of images are from the same person or from different people.
        ((MainContext*)context)->log("Found "+std::to_string(faceImgs.size())+" faces");
        std::vector<dlib::matrix<float, 0, 1>> face_descriptors = net(faceImgs);
        for(int i=0; i<face_descriptors.size(); i++){
            cv::Rect faceRect;
            faceRect.x= (int)faces[i].left();
            faceRect.y= (int)faces[i].top();
            faceRect.height= (int)(faces[i].right()-faces[i].left());
            faceRect.width= (int)(faces[i].bottom()-faces[i].top());
            cv::rectangle(imgBuff, faceRect, cvScalar(0, 0, 255), 2);
            int idx= FaceModel::findSimilar(faceModels, face_descriptors[i]);

            if(idx!=FACEMODEL_FACE_NONE)
                ((MainContext*)context)->onFaceDetected(faceModels[idx]->getName());
            else {
                ((MainContext *) context)->onFaceDetected("");
            }
        }
    } else {
        ((MainContext*)context)->log("");
        ((MainContext *) context)->onFaceDetected("");
    }

    ((MainContext*)context)->showImage(imgBuff);
    //###################
}

void FaceRecognizer::onStop() {

}
