#include "FaceFinder.h"

FaceFinder::FaceFinder(DataProcessor *dataProcessor) {
    this->dataProcessor= dataProcessor;
    imgsLock= PTHREAD_MUTEX_INITIALIZER;
}

vector<dlib::matrix<dlib::rgb_pixel>>* FaceFinder::getFaceImgs() {
    return &faceImgs;
}

void FaceFinder::getFaceImgs(vector<dlib::matrix<dlib::rgb_pixel>> * faceImgs) {
    pthread_mutex_lock(&imgsLock);
    faceImgs->swap(this->faceImgs);
    pthread_mutex_unlock(&imgsLock);
}

int FaceFinder::getFaceImgsSize() {
    int size;

    pthread_mutex_lock(&imgsLock);
    size= faceImgs.size();
    pthread_mutex_unlock(&imgsLock);

    return size;
}


void FaceFinder::onStart() {
    //Init camera
    camera= new Camera();
    camera->init(512, 512);

    //Init dlib face detector
    face_detector= dlib::get_frontal_face_detector();
    dlib::deserialize(dataProcessor->getRealPath("/data/ai_models/shape_predictor_5_face_landmarks.dat")) >> sp;
}

void FaceFinder::onRun() {
    //Get camera image
    camera->getImage(&imgBuff);
    //Convert to dlib/opencv image
    dlib::cv_image<dlib::bgr_pixel> tmp(imgBuff);
    dlib::matrix<dlib::rgb_pixel> img;
    dlib::assign_image(img, tmp);
    //Search for faces
    std::vector<dlib::rectangle> faces=face_detector(img);

    //Extract each face as 150x150px image

    faceImgsBuff.clear();

    for(int i=0; i<faces.size(); i++){
        auto shape= sp(img, faces[i]);
        dlib::matrix<dlib::rgb_pixel> face_chip;
        dlib::extract_image_chip(img, dlib::get_face_chip_details(shape, 150, 0.25), face_chip);

        faceImgsBuff.push_back(move(face_chip));
    }

    pthread_mutex_lock(&imgsLock);
    faceImgs.swap(faceImgsBuff);
    pthread_mutex_unlock(&imgsLock);

}

void FaceFinder::onStop() {

}
