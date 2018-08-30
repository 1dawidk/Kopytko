#include "ClockView.h"

ClockView::ClockView() {
    this->override_font(*(new Pango::FontDescription("sans bold 28")));
    this->set_max_width_chars(50);
    this->Start();
}

void ClockView::Run() {
    int lastTime=0;
    char timeText[10];


    while(runThread){
        if(Clock::GetDayMinutes()!=lastTime){
            lastTime= Clock::GetDayMinutes();
            sprintf(timeText, "%02d : %02d", lastTime/60, lastTime%60);
            this->set_text(timeText);
        }
    }


}

void ClockView::Stop() {

}
