#ifndef MORTFIRMWARE_CAMERA_H
#define MORTFIRMWARE_CAMERA_H

#ifndef DEBUG1
#include <raspicam/raspicam.h>
#include <raspicam/raspicam_cv.h>
using namespace raspicam;
#endif

#ifdef DEBUG1

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <highgui.h>

#endif



class Camera {
public:
    Camera();
    ~Camera();
    void init(unsigned int resX, unsigned int resY);

    int getImage(cv::Mat *buf);

private:
    unsigned int resY;
    unsigned int resX;

#ifndef DEBUG1
    RaspiCam_Cv *cam_h;
#endif
};


#endif //MORTFIRMWARE_CAMERA_H
