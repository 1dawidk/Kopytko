#include "FaceRecognizer.h"


FaceRecognizer::FaceRecognizer(UI *ui){
    this->ui= ui;
    this->dataProcessor= dataProcessor;
}


void FaceRecognizer::onStart() {
    //Init camera
    camera= new Camera();
    camera->init(512, 512);

    //Init dlib face detector
    face_detector= dlib::get_frontal_face_detector();

    //Init dlib face detector
    dlib::deserialize(dataProcessor->getRealPath("/data/ai_models/shape_predictor_5_face_landmarks.dat")) >> sp;
    dlib::deserialize(dataProcessor->getRealPath("/data/ai_models/dlib_face_recognition_resnet_model_v1.dat")) >> net;

    //Load face models
    FaceModel::readModelsFile(dataProcessor, faceModels, "known_faces");

    ui->faceDetectedCallback(FACE_NO_FACE);
}

void FaceRecognizer::onRun() {

    //Get camera image
    camera->getImage(&imgBuff);
    //Convert to dlib/opencv image
    dlib::cv_image<dlib::bgr_pixel> tmp(imgBuff);
    dlib::matrix<dlib::rgb_pixel> img;
    dlib::assign_image(img, tmp);

    //if needed kill thread
    if(!runThread)
        return;

    //Search for faces
    std::vector<dlib::rectangle> faces=face_detector(img);


    //if needed kill thread
    if(!runThread)
        return;

    //Extract each face as 150x150px image
    vector<dlib::matrix<dlib::rgb_pixel>> faceImgs;
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

        //if needed kill thread
        if(!runThread)
            return;

        std::vector<dlib::matrix<float, 0, 1>> face_descriptors = net(faceImgs);
        for(int i=0; i<face_descriptors.size(); i++){
            int idx= FaceModel::findSimilar(faceModels, face_descriptors[i]);

            if(idx!=FACEMODEL_FACE_NONE) {
                Log::write("FaceRecognizer", "Face id: %d", faceModels[idx]->getFaceId());
                ui->faceDetectedCallback(faceModels[idx]->getFaceId());
            }else {
                ui->faceDetectedCallback(FACE_UNKNOWN);
                faceModels.push_back(new FaceModel(3, face_descriptors[i]));
                FaceModel::writeModelsFile(dataProcessor, faceModels, "known_faces");
            }
        }
    } else {
        ui->log("");
        ui->faceDetectedCallback(FACE_NO_FACE);
    }
    //###################
}

void FaceRecognizer::onStop() {
    //faceFinder->stop();
}
