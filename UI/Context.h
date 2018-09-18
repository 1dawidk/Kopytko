#ifndef KOPYTKO_CONTEXT_H
#define KOPYTKO_CONTEXT_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <UI/Views/ClockView.h>
#include <UI/Views/DebugView.h>
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <dlib/matrix/matrix.h>
#include <dlib/pixel.h>

#define OPEN_FILE_MODE_RELATIVE 0
#define OPEN_FILE_MODE_ABSOLUTE 1

class FaceRecognizer; //#include "AI/FaceRecognizer.h"

class Context : public Gtk::Window{
public:
    void init(string runPath);

    void showImage(cv::Mat img);
    void onFaceDetected(string label);
    void log(string msg);

    void onShowImage();
    void onLabelChange();

    ofstream openWriteFile(string path, int mode);
    ifstream openReadFile(string path, int mode);

private:
    string buildPath;

    Gtk::Box *box;

    //Views
    ClockView *clockView;
    DebugView *debugView;
    Gtk::Image *imageView;
    Gtk::Label nameLabel;

    //GUI Thread
    Glib::Dispatcher imgShowDispatcher;
    Glib::Dispatcher labelChangeDispatcher;

    //Other
    FaceRecognizer *faceRecognizer;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
    string label;
};


#endif //KOPYTKO_CONTEXT_H
