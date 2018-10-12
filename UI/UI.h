#ifndef KOPYTKO_MAINCONTEXT_H
#define KOPYTKO_MAINCONTEXT_H

//MainContext
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
#include <Session.h>

using namespace std;
class FaceRecognizer; //#include "AI/FaceRecognizer.h"

class UI : public Gtk::Window{
public:
    UI(DataProcessor *dataProcessor);
    void init();

    void showImage(cv::Mat img);
    void faceDetectedCallback(int userId);
    void log(string msg);

    void onShowImage();
    void onLabelChange();

    ofstream openWriteFile(string path, int mode);
    ifstream openReadFile(string path, int mode);

    //Statics
    static int prcToPix(int prc, int dir);

private:
    bool onKeyPress(GdkEventKey* event);

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
    DataProcessor *dataProcessor;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
    string label;
    string lastLabel;

    //Sessins
    vector<Session*> sessions;
    int runningSession;



    //Statics
    static int winW;
    static int winH;
};


#endif //KOPYTKO_MAINCONTEXT_H
