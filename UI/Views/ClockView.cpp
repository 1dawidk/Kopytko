#include "ClockView.h"

ClockView::ClockView() {
    Gdk::Color textColor= Gdk::Color("white");
    this->modify_font(*(new Pango::FontDescription("sans bold 28")));
    this->modify_fg(Gtk::STATE_NORMAL, textColor);
    this->set_max_width_chars(50);
    this->set_text("00:00");

    worker= Glib::Thread::create(
            sigc::mem_fun(*this, &ClockView::work), true);
}

ClockView::~ClockView() {
    workAct=false;
    worker->join();
}

void ClockView::work() {
    int lastTime=0;
    char timeText[10];

    lastTime= Clock::GetDayMinutes();
    sprintf(timeText, "%02d : %02d", lastTime/60, lastTime%60);
    this->set_text(timeText);
    workAct=true;

    while(workAct){
        if(Clock::GetDayMinutes()!=lastTime){
            lastTime= Clock::GetDayMinutes();
            sprintf(timeText, "%02d : %02d", lastTime/60, lastTime%60);
            this->set_text(timeText);
        }
    }
}
