#include "Context.h"
#include "AI/FaceRecognizer.h"


void Context::init(string runPath) {
    //Get build DIRECTORY not app run path
    size_t lastSlash= runPath.find_last_of('/');
    buildPath= runPath.substr(0, lastSlash);
    buildPath+="/..";


    //Main background color
    Gdk::Color bg_color("black");

    box= new Gtk::VBox();

    //Create and add Views
    clockView= new ClockView();
    imageView= new Gtk::Image();
    debugView= new DebugView(10);
    box->pack_start(*clockView, Gtk::PACK_SHRINK);
    box->pack_start(*debugView, Gtk::PACK_SHRINK);
    box->pack_start(nameLabel, Gtk::PACK_SHRINK);
    box->pack_start(*imageView);

    box->show_all_children(true);
    box->show();

    faceRecognizer= new FaceRecognizer(this);
    faceRecognizer->start();

    this->add(*box);
    this->modify_bg(Gtk::STATE_NORMAL, bg_color);
    this->fullscreen();

    imgShowDispatcher.connect(
            sigc::mem_fun(*this, &Context::onShowImage));
    labelChangeDispatcher.connect(
            sigc::mem_fun(*this, &Context::onLabelChange));
}

void Context::showImage(cv::Mat img){
    pixbuf = Gdk::Pixbuf::create_from_data(img.data, Gdk::COLORSPACE_RGB, false, 8,
                                                                     img.cols, img.rows, img.step);
    imgShowDispatcher();
}

void Context::onShowImage() {
    imageView->set(pixbuf);
}

void Context::onLabelChange() {
    if(!label.empty()) {
        nameLabel.set_text("Hello "+label+" :)");
    } else {
        nameLabel.set_text("Looking for someone...");
    }
}

void Context::onFaceDetected(string label){
    this->label= label;
    labelChangeDispatcher();
}

void Context::log(string msg) {
    debugView->log(msg);
}

ofstream Context::openWriteFile(string path, int mode) {
    ofstream file;

    if(mode==OPEN_FILE_MODE_RELATIVE) {
        file.open(buildPath + path, ios::out | ios::trunc);
    } else {
        char rpath[255];
        realpath(path.c_str(), rpath);
        file.open(rpath, ios::out | ios::trunc);
    }

    if(!file.is_open())
        log("Error opening file: "+path+" !");

    return file;
}

ifstream Context::openReadFile(string path, int mode) {
    ifstream file;

    if(mode==OPEN_FILE_MODE_RELATIVE) {
        file.open(buildPath + path, ios::in);
    } else {
        char rpath[255];
        realpath(path.c_str(), rpath);
        file.open(rpath, ios::in);
    }

    if(!file.is_open())
        log("Error opening file: "+path+" !g");

    return file;
}
