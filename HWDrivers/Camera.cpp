#include <zconf.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include "Camera.h"

#ifndef DEBUG1

Camera::Camera() {
    cam_h= new RaspiCam();
}

Camera::~Camera() {
    cam_h->release();
    delete cam_h;
}

void Camera::init(unsigned int resX, unsigned int resY) {
    cam_h->setWidth ( resX );
    cam_h->setHeight ( resY );
    this->resX= resX;
    this->resY= resY;
    cam_h->setBrightness ( 50 );

    cam_h->setBrightness ( 50 );

    cam_h->setSharpness (0 );
    cam_h->setContrast ( 0  );
    cam_h->setSaturation ( 0 );
    cam_h->setShutterSpeed( 0 );
    cam_h->setISO ( 400 );
    cam_h->setAWB_RB(1, 1);

    cam_h->setExposureCompensation ( 0  );

    cam_h->setRotation(180);

    cam_h->open();
    sleep(3);
}

int Camera::getImage(uint8_t *buf) {
    cam_h->grab();
    cam_h->retrieve(buf);

    return 1;
}

uint8_t *Camera::createBuf() {
    return new uint8_t[cam_h->getImageBufferSize()];
}

int Camera::getReqBufLen() {
    return cam_h->getImageBufferSize();
}

unsigned int Camera::getResY(){
    return resY;
}

unsigned int Camera::getResX(){
    return resX;
}

#endif

#ifdef DEBUG1

Camera::Camera() {
}

Camera::~Camera() {
}

void Camera::init(unsigned int resX, unsigned int resY) {
    //cap= new cv::VideoCapture(0);
}

int Camera::getImage(uint8_t *buf) {

}

uint8_t *Camera::createBuf() {

}

int Camera::getReqBufLen() {

}

unsigned int Camera::getResY(){
    return resY;
}

unsigned int Camera::getResX(){
    return resX;
}

#endif