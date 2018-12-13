#ifndef KOPYTKO_MAINCONTEXT_H
#define KOPYTKO_MAINCONTEXT_H

//MainContext
#include <UI/Views/ClockView.h>
#include <UI/Views/DebugView.h>
#include <UI/Views/HeartbeatView.h>
#include <UI/Views/ICMWeatherView.h>
#include <UI/Voice.h>

#include <Logic/HWDrivers/SoundRecorder.h>

//Gtk
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/main.h>

//Dlib
#include <dlib/matrix/matrix.h>
#include <dlib/pixel.h>

//OpenCV
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <Session.h>
#include <Logic/AI/VoiceRecognition/VoiceRecognizer.h>

#define UI_VERTICAL    0
#define UI_HORIZONTAL  1

#define UI_NO_SESSION_RUNNING -1

using namespace std;
class FaceRecognizer; //#include "AI/FaceRecognizer.h"

class UI : public Gtk::Window{
public:
    virtual ~UI();

    void init();
    void stop();

    void log(string msg);

    void onShowImage();
    void onLabelChange();
    void onSessionAction();

    void showImageCallback(cv::Mat img);
    void faceDetectedCallback(int userId);
    void setRightViewCallback();
    void setMiddleViewCallback();
    void setLeftViewCallback();

    //Statics
    static int prcToPix(int prc, int dir);

private:
    bool onKeyPress(GdkEventKey* event);


    //Containers
    Gtk::Box *headerBox;
    Gtk::Box *midBox;
    Gtk::Box *notiBox;
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
    VoiceRecognizer *voiceRecognizer;
    Voice *voice;

    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
    string label;
    string lastLabel;

    //Session
    Glib::Dispatcher sessionDispatcher;
    Session* session;

    //Statics
    static int winW;
    static int winH;
};


#endif //KOPYTKO_MAINCONTEXT_H
