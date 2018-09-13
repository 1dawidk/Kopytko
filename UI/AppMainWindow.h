#ifndef KOPYTKO_APPMAINWINDOW_H
#define KOPYTKO_APPMAINWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <UI/Views/ClockView.h>
#include <UI/Views/DebugView.h>
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <dlib/matrix/matrix.h>
#include <dlib/pixel.h>

class FaceRecognizer; //#include "AI/FaceRecognizer.h"

class AppMainWindow : public Gtk::Window{
public:
    void init();

    void showImage(cv::Mat img);
    void onFaceDetected(int id);
    void log(string msg);

    void onShowImage();

private:
    Gtk::Box *box;

    //Views
    ClockView *clockView;
    DebugView *debugView;
    Gtk::Image *imageView;
    Gtk::Label nameLabel;

    //GUI Thread
    Glib::Dispatcher imgShowDispatcher;

    //Other
    FaceRecognizer *faceRecognizer;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
};


#endif //KOPYTKO_APPMAINWINDOW_H
