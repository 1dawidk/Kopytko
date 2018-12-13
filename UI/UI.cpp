#include "UI.h"
#include "Logic/AI/FaceRecognition/FaceRecognizer.h"
#include <Debug/Log.h>

int UI::winW=0;
int UI::winH=0;

/***************** PUBLIC METHODS *********************/

void UI::init() {
    voice= new Voice();
    voice->init("/voice_words");
    voice->say("cmd_greeting");

    Glib::RefPtr<Gdk::Screen> screen= Gdk::Screen::get_default();
    winW= screen->get_width();
    winH= screen->get_height();

    //Create views and boxes
    mainBox= Gtk::manage(new Gtk::VBox());
    headerBox= Gtk::manage(new Gtk::HBox());
    midBox= Gtk::manage(new Gtk::HBox());
    notiBox= Gtk::manage(new Gtk::VBox());
    midMidBox= Gtk::manage(new Gtk::VBox());
    rightMidBox= Gtk::manage(new Gtk::VBox());
    bottomBox= Gtk::manage(new Gtk::HBox());

    clockView= Gtk::manage(new ClockView());
    clockView->resize(58);
    imageView= Gtk::manage(new Gtk::Image());
    icmWeatherView= Gtk::manage(new ICMWeatherView());
    icmWeatherView->setCity("Warszawa");
    heartbeatView= Gtk::manage(new HeartbeatView());

    //Prepare views and boxes
    midBox->pack_start(*notiBox, Gtk::PACK_EXPAND_WIDGET);
    midBox->pack_start(*midMidBox, Gtk::PACK_EXPAND_WIDGET);
    midBox->pack_start(*rightMidBox, Gtk::PACK_EXPAND_WIDGET);
    nameLabel.modify_font(*(new Pango::FontDescription("sans bold 28")));
    nameLabel.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("white"));

    //Add views to boxes
    headerBox->pack_start(*clockView, Gtk::PACK_EXPAND_PADDING);
    bottomBox->pack_end(*heartbeatView, Gtk::PACK_SHRINK);
    midMidBox->pack_start(nameLabel, Gtk::PACK_SHRINK);
    //midMidBox->pack_start(*imageView);
    midMidBox->pack_start(*icmWeatherView);


    //Show boxes all children
    headerBox->show_all_children(true);
    midBox->show_all_children(true);
    notiBox->show_all_children(true);
    midMidBox->show_all_children(true);
    rightMidBox->show_all_children(true);
    bottomBox->show_all_children(true);

    //Pack layout boxes
    mainBox->pack_start(*headerBox, Gtk::PACK_SHRINK);
    mainBox->pack_start(*midBox, Gtk::PACK_EXPAND_WIDGET);
    mainBox->pack_end(*bottomBox, Gtk::PACK_EXPAND_WIDGET);
    mainBox->show_all_children(true);

    //Set context view and show main box
    mainBox->show();
    this->add(*mainBox);

    //Setup layout params
    Gdk::Color bg_color("black");
    this->modify_bg(Gtk::STATE_NORMAL, bg_color);
    this->fullscreen();

    //Create and prepare Face Recognizer
    faceRecognizer= new FaceRecognizer(this);
    faceRecognizer->start();

    //Create dispatchers
    imgShowDispatcher.connect(
            sigc::mem_fun(*this, &UI::onShowImage));
    labelChangeDispatcher.connect(
            sigc::mem_fun(*this, &UI::onLabelChange));

    this->signal_key_press_event().connect(
            sigc::mem_fun(*this, &UI::onKeyPress), false);

    //Prepare session environment
    session= NULL;
    sessionDispatcher.connect(
            sigc::mem_fun(*this, &UI::onSessionAction));


    voiceRecognizer= new VoiceRecognizer();
    voiceRecognizer->start();

    voice->say("cmd_ready");
}



void UI::onShowImage() {
    //imageView->set(pixbuf);
}

void UI::onLabelChange() {
    if(!label.empty()) {
        nameLabel.set_text("Hello "+label+" :)");
        if(label=="Dawid" && lastLabel!=label) {
            clockView->resize(32);
            icmWeatherView->show();
            //icmWeatherView->refreshWeather();
        }
    } else {
        nameLabel.set_text("Looking for someone...");
        icmWeatherView->hide();
        clockView->resize(58);
    }

    lastLabel= label;
}

void UI::onSessionAction() {

}


void UI::log(string msg) {
    heartbeatView->makeBeat(msg);
}


/***************** CALLBACKS ************************/

void UI::showImageCallback(cv::Mat img){
    pixbuf = Gdk::Pixbuf::create_from_data(img.data, Gdk::COLORSPACE_RGB, false, 8,
                                           img.cols, img.rows, img.step);
    heartbeatView->makeBeat();
    imgShowDispatcher();
}

void UI::faceDetectedCallback(int userId){
    Log::write("UI", "Face detected with id %d", userId);
    //If face is present
    if(userId!=FACE_NO_FACE) {
        //If face is unknown
        if(userId==FACE_UNKNOWN){
            //Close session
            session->stop();
            delete session;
        } else {
            //If there is no session running
            if (session==NULL) {
                //Open new session
                Log::write("UI", "Run session");
                session= new Session(userId, this);
                voice->say("hello %s", (session->getUserName()).c_str());
            //If same user detected
            } else if(session->getUserId()==userId) {
                session->refresh();
            //If other user was detected
            } else {
                //Close previous session
                session->stop();
                delete session;

                //Open new session
                Log::write("UI", "Change session");
                session= new Session(userId, this);
                voice->say("hello %s", (session->getUserName()).c_str());
            }
        }
    //If no face found
    } else {
        //Check if there is session and if it should be closed
        if(session!=NULL && session->getUpTime()>SESSION_IDLE_MAX_DURATION_S) {
            session->stop();
            delete session;
            session = NULL;
        }
    }
}

void UI::setRightViewCallback() {

}

void UI::setMiddleViewCallback() {

}

void UI::setLeftViewCallback() {

}

/********************* STATICS ************************/

int UI::prcToPix(int prc, int dir) {
    if(dir==UI_VERTICAL)
        return (prc*winH)/100;
    else if(dir==UI_HORIZONTAL)
        return (prc*winW)/100;
    else
        return 0;
}


/***************** PRIVATE METHODS ********************/

bool UI::onKeyPress(GdkEventKey *event) {
    if(event->keyval==65307 && event->hardware_keycode==9 && event->state==0) {
        Log::write("UI", "Closing Kopytko system");
        voice->say("cmd_bye");
        Gtk::Main::quit();
    }

    return false;
}

UI::~UI() {
    //icmWeatherView->stop();
    Log::write("UI", "Stop: Voice Recognizer");
    voiceRecognizer->stop();
    Log::write("UI", "Stop: Face Recognizer");
    faceRecognizer->stop();
    Log::write("UI", "Stop: Voice");
    voice->stop();
    Log::write("UI", "Bye bye");
}
