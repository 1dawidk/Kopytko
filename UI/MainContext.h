#ifndef KOPYTKO_MAINCONTEXT_H
#define KOPYTKO_MAINCONTEXT_H

//UI
#include <UI/Context.h>
#include <UI/Views/ClockView.h>
#include <UI/Views/DebugView.h>
#include <UI/Views/HeartbeatView.h>
#include <UI/Views/ICMWeatherView.h>

//Gtk
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>

//Dlib
#include <dlib/matrix/matrix.h>
#include <dlib/pixel.h>

//OpenCV
#include <opencv2/core/core.hpp>
#include <cv.h>

using namespace std;
class FaceRecognizer; //#include "AI/FaceRecognizer.h"

class MainContext : public Context {
public:
    MainContext(string runPath);
    void init() override;

    void showImage(cv::Mat img);
    void onFaceDetected(string label);
    void log(string msg);

    void onShowImage();
    void onLabelChange();

private:
    Gtk::Box *topBox;
    Gtk::Box *midBox;
    Gtk::Box *leftMidBox;
    Gtk::Box *midMidBox;
    Gtk::Box *rightMidBox;
    Gtk::Box *bottomBox;

    Gtk::Box *mainBox;

    //Views
    ClockView *clockView;
    HeartbeatView *heartbeatView;
    ICMWeatherView *icmWeatherView;
    Gtk::Image *imageView;
    Gtk::Label nameLabel;

    //GUI Thread
    Glib::Dispatcher imgShowDispatcher;
    Glib::Dispatcher labelChangeDispatcher;

    //Other
    FaceRecognizer *faceRecognizer;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
    string label;
    string lastLabel;
};


#endif //KOPYTKO_MAINCONTEXT_H
