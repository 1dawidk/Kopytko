#ifndef KOPYTKO_APPMAINWINDOW_H
#define KOPYTKO_APPMAINWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <UI/Views/ClockView.h>
#include <opencv2/core/core.hpp>
#include <cv.h>

class FaceRecognizer; //#include "AI/FaceRecognizer.h"

class AppMainWindow : public Gtk::Window{
public:
    void init();

    void showImage(cv::Mat img);
    void onFaceDetected(int id);

private:
    Gtk::Box *box;

    //Views
    ClockView *clockView;
    Gtk::Image *imageView;
    Gtk::Label nameLabel;

    //Other
    FaceRecognizer *faceRecognizer;
};


#endif //KOPYTKO_APPMAINWINDOW_H
