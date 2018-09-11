#include <cv.h>
#include "AppMainWindow.h"
#include "AI/FaceRecognizer.h"


void AppMainWindow::init() {
    Gdk::Color bg_color("black");

    box= new Gtk::VBox();

    //Create and add Views
    clockView= new ClockView();
    imageView= new Gtk::Image();
    box->pack_start(*clockView, Gtk::PACK_SHRINK);
    box->pack_start(nameLabel);
    box->pack_start(*imageView);

    box->show_all_children(true);
    box->show();

    faceRecognizer= new FaceRecognizer(this);
    faceRecognizer->start();

    this->add(*box);
    this->modify_bg(Gtk::STATE_NORMAL, bg_color);
    this->fullscreen();
}

void AppMainWindow::showImage(cv::Mat img){
    cv::Mat rgbImg;
    cv::cvtColor(img, rgbImg, CV_BGR2RGB);
    Glib::RefPtr<Gdk::Pixbuf> pixbuf= Gdk::Pixbuf::create_from_data(img.data, Gdk::COLORSPACE_RGB ,false, 8, img.cols, img.rows, img.step);
    imageView->set(pixbuf);
}

void AppMainWindow::onFaceDetected(int id){
    nameLabel.set_text("Hello Dawid :)");
}