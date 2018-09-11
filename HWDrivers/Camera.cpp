#include <zconf.h>
#include <fcntl.h>
#include "Camera.h"

#ifndef DEBUG1
Camera::Camera() {
    cam_h= new RaspiCam_Cv();
}

Camera::~Camera() {
    cam_h->release();
    delete cam_h;
}

void Camera::init(unsigned int resX, unsigned int resY) {
    cam_h->set(CV_CAP_PROP_FRAME_WIDTH, resX);
    cam_h->set(CV_CAP_PROP_FRAME_HEIGHT, resY);
    //cam_h->set(CV_CAP_PROP_ROLL, 180);

    this->resX= resX;
    this->resY= resY;

    cam_h->open();
    sleep(3);
}

int Camera::getImage(cv::Mat *buf) {
    cam_h->grab();
    cam_h->retrieve(*buf);

    return 1;
}

#endif

#ifdef DEBUG1

Camera::Camera() {
}

Camera::~Camera() {
}

void Camera::init(unsigned int resX, unsigned int resY) {

}

int Camera::getImage(cv::Mat *buf) {
    cv::VideoCapture capture(0);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 1024);
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 1024);
    capture.read(*buf);
}

#endif