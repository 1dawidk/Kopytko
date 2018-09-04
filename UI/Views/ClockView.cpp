#include "ClockView.h"

ClockView::ClockView() {
    this->override_font(*(new Pango::FontDescription("sans bold 28")));
    this->set_max_width_chars(50);
    this->set_text("00:00");
    this->start();
}

ClockView::~ClockView() {
    this->stop();
}

void ClockView::run() {
    int lastTime=0;
    char timeText[10];

    lastTime= Clock::GetDayMinutes();
    sprintf(timeText, "%02d : %02d", lastTime/60, lastTime%60);
    this->set_text(timeText);
    runThread=true;

    while(runThread){
        if(Clock::GetDayMinutes()!=lastTime){
            lastTime= Clock::GetDayMinutes();
            sprintf(timeText, "%02d : %02d", lastTime/60, lastTime%60);
            this->set_text(timeText);
        }
    }
}

void ClockView::stop() {
    runThread= false;
}
