#ifndef MORTFIRMWARE_CAMERA_H
#define MORTFIRMWARE_CAMERA_H

#include <raspicam/raspicam.h>

#ifdef DEBUG1

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/v4l2-common.h>
#include <linux/v4l2-controls.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <string.h>
#include <fstream>
#include <string>

#endif

using namespace raspicam;

class Camera {
public:
    Camera();
    ~Camera();
    void init(unsigned int resX, unsigned int resY);

    int getImage(uint8_t *buf);
    uint8_t* createBuf();
    int getReqBufLen();

    unsigned int getResY();
    unsigned int getResX();

private:
    unsigned int resY;
    unsigned int resX;

#ifndef DEBUG1
    RaspiCam *cam_h;
#else
    int fd;
#endif
};


#endif //MORTFIRMWARE_CAMERA_H
