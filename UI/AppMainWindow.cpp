#include "AppMainWindow.h"
#include "AI/FaceRecognizer.h"


void AppMainWindow::init() {
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
            sigc::mem_fun(*this, &AppMainWindow::onShowImage));
}

void AppMainWindow::showImage(cv::Mat img){
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

    pixbuf = Gdk::Pixbuf::create_from_data(img.data, Gdk::COLORSPACE_RGB, false, 8,
                                                                     img.cols, img.rows, img.step);
    imgShowDispatcher();
}

void AppMainWindow::onShowImage() {
    imageView->set(pixbuf);
}

void AppMainWindow::onFaceDetected(int id){
    if(id) {
        //nameLabel.set_text("Hello Dawid :)");
    } else {
        //nameLabel.set_text("Looking for someone...");
    }
}

void AppMainWindow::log(string msg) {
    debugView->log(msg);
}
