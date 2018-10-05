#include "MainContext.h"
#include "AI/FaceRecognizer.h"

MainContext::MainContext(string runPath) : Context(runPath) {
}

void MainContext::init() {
    Context::init();

    //Create views and boxes
    mainBox= Gtk::manage(new Gtk::VBox());
    topBox= Gtk::manage(new Gtk::HBox());
    midBox= Gtk::manage(new Gtk::HBox());
    leftMidBox= Gtk::manage(new Gtk::VBox());
    midMidBox= Gtk::manage(new Gtk::VBox());
    rightMidBox= Gtk::manage(new Gtk::VBox());
    bottomBox= Gtk::manage(new Gtk::HBox());

    clockView= Gtk::manage(new ClockView());
    imageView= Gtk::manage(new Gtk::Image());
    icmWeatherView= Gtk::manage(new ICMWeatherView(this));
    icmWeatherView->setCity("Warszawa");
    heartbeatView= Gtk::manage(new HeartbeatView());

    //Prepare views and boxes
    midBox->pack_start(*leftMidBox, Gtk::PACK_EXPAND_WIDGET);
    midBox->pack_start(*midMidBox, Gtk::PACK_EXPAND_WIDGET);
    midBox->pack_start(*rightMidBox, Gtk::PACK_EXPAND_WIDGET);
    nameLabel.modify_font(*(new Pango::FontDescription("sans bold 28")));

    //Add views to boxes
    topBox->pack_start(*clockView, Gtk::PACK_EXPAND_PADDING);
    bottomBox->pack_end(*heartbeatView, Gtk::PACK_SHRINK);
    midMidBox->pack_start(nameLabel, Gtk::PACK_SHRINK);
    //midMidBox->pack_start(*imageView);
    //midMidBox->pack_start(*icmWeatherView);


    //Show boxes all children
    topBox->show_all_children(true);
    midBox->show_all_children(true);
    leftMidBox->show_all_children(true);
    midMidBox->show_all_children(true);
    rightMidBox->show_all_children(true);
    bottomBox->show_all_children(true);

    //Pack layout boxes
    mainBox->pack_start(*topBox, Gtk::PACK_SHRINK);
    mainBox->pack_start(*midBox, Gtk::PACK_EXPAND_WIDGET);
    mainBox->pack_end(*bottomBox, Gtk::PACK_EXPAND_WIDGET);
    mainBox->show_all_children(true);

    //Set context view and show main box
    mainBox->show();
    this->setContextView(mainBox);

    //Setup layout params
    Gdk::Color bg_color("black");
    this->modify_bg(Gtk::STATE_NORMAL, bg_color);
    this->fullscreen();

    //Create and prepare Face Recognizer
    faceRecognizer= new FaceRecognizer(this);
    faceRecognizer->start();

    //Create dispatchers
    imgShowDispatcher.connect(
            sigc::mem_fun(*this, &MainContext::onShowImage));
    labelChangeDispatcher.connect(
            sigc::mem_fun(*this, &MainContext::onLabelChange));

    this->signal_key_press_event().connect(
            sigc::mem_fun(*this, &MainContext::onKeyPress), false);
}

void MainContext::showImage(cv::Mat img){
    pixbuf = Gdk::Pixbuf::create_from_data(img.data, Gdk::COLORSPACE_RGB, false, 8,
                                           img.cols, img.rows, img.step);
    heartbeatView->makeBeat();
    imgShowDispatcher();
}

void MainContext::onShowImage() {
    imageView->set(pixbuf);
}

void MainContext::onLabelChange() {
    if(!label.empty()) {
        nameLabel.set_text("Fak ju "+label+" :)");
        if(label=="Dawid" && lastLabel!=label) {
            midMidBox->pack_start(*icmWeatherView);
            midMidBox->show_all_children(true);
            icmWeatherView->refreshWeather();
        }
    } else {
        nameLabel.set_text("Looking for someone...");
    }

    lastLabel= label;
}

void MainContext::onFaceDetected(string label){
    this->label= label;

    heartbeatView->makeBeat();
    labelChangeDispatcher();
}

void MainContext::log(string msg) {
    heartbeatView->makeBeat(msg);
}

bool MainContext::onKeyPress(GdkEventKey *event) {
    if(event->keyval==65307 && event->hardware_keycode==9 && event->state==0) {
        cout << "Close app";
    }

    return false;
}
