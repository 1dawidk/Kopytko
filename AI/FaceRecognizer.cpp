#include "FaceRecognizer.h"


//ITS A KIND OF MAGIC
template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = dlib::add_prev1<block<N,BN,1,dlib::tag1<SUBNET>>>;

template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = dlib::add_prev2<dlib::avg_pool<2,2,2,2,dlib::skip1<dlib::tag2<block<N,BN,2,dlib::tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET>
using block  = BN<dlib::con<N,3,3,1,1,dlib::relu<BN<dlib::con<N,3,3,stride,stride,SUBNET>>>>>;

template <int N, typename SUBNET> using ares      = dlib::relu<residual<block,N,dlib::affine,SUBNET>>;
template <int N, typename SUBNET> using ares_down = dlib::relu<residual_down<block,N,dlib::affine,SUBNET>>;

template <typename SUBNET> using alevel0 = ares_down<256,SUBNET>;
template <typename SUBNET> using alevel1 = ares<256,ares<256,ares_down<256,SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128,ares<128,ares_down<128,SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64,ares<64,ares<64,ares_down<64,SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32,ares<32,ares<32,SUBNET>>>;

using anet_type = dlib::loss_metric<dlib::fc_no_bias<128,dlib::avg_pool_everything<
                                             alevel0<
                                             alevel1<
                                             alevel2<
                                             alevel3<
                                             alevel4<
                                             dlib::max_pool<3,3,2,2,dlib::relu<dlib::affine<dlib::con<32,7,7,2,2,
                                             dlib::input_rgb_image_sized<150>
                                             >>>>>>>>>>>>;

//END OF A KIND OF MAGIC

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
    dlib::frontal_face_detector face_detector= dlib::get_frontal_face_detector();
    dlib::shape_predictor sp;
    dlib::deserialize("../AI/data/shape_predictor_5_face_landmarks.dat") >> sp;
    anet_type net;
    dlib::deserialize("../AI/data/dlib_face_recognition_resnet_model_v1.dat") >> net;


    while (runThread){
        context->log("---------------------------------------");
        //Get camera image
        context->log("Get camera image...");
        camera->getImage(&imgBuff);
        //Convert to dlib/opencv image
        context->log("Convert for rgb matrix...");
        dlib::cv_image<dlib::bgr_pixel> tmp(imgBuff);
        dlib::matrix<dlib::rgb_pixel> img;
        dlib::assign_image(img, tmp);
        //Search for faces
        context->log("Find faces...");
        std::vector<dlib::rectangle> faces=face_detector(img);

        std::vector<dlib::matrix<dlib::rgb_pixel>> faceImgs;

        context->log("Get faces chips...");
        //Extract each face as 150x150px image
        for(int i=0; i<faces.size(); i++){
            auto shape= sp(img, faces[i]);
            dlib::matrix<dlib::rgb_pixel> face_chip;

            string msg= "Extracting chip ";
            msg+=std::to_string(i+1);
            msg+=" ...";
            context->log(msg);
            dlib::extract_image_chip(img, dlib::get_face_chip_details(shape, 150, 0.25), face_chip);
            faceImgs.push_back(move(face_chip));
        }


        if(!faceImgs.empty()) {
            // This call asks the DNN to convert each face image in faces into a 128D vector.
            // In this 128D vector space, images from the same person will be close to each other
            // but vectors from different people will be far apart.  So we can use these vectors to
            // identify if a pair of images are from the same person or from different people.
            context->log("Face recognizing net working...");
            std::vector<dlib::matrix<float, 0, 1>> face_descriptors = net(faceImgs);
            context->log("Face recognizing net working [ Done ]");
            context->log("Descriptors: ");
            for(int i=0; i<face_descriptors.size(); i++){
                string col_str="[ ";
                for(int j=0; j<face_descriptors[i].nr(); j++){
                    col_str+=std::to_string(face_descriptors[i](j,0))+", ";
                }

                col_str+="]";
                context->log("Face "+std::to_string(i+1)+": "+col_str);
            }

            context->onFaceDetected(1);

        } else {
            context->onFaceDetected(0);
        }

        context->log("Show image...");
        context->showImage(imgBuff);
        context->log("---------------------------------------");
        //###################
    }
}
