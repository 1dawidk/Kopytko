#include "HeartbeatView.h"

HeartbeatView::HeartbeatView() {
    beatDispatcher.connect(
            sigc::mem_fun(*this, &HeartbeatView::onBeat));
}

void HeartbeatView::makeBeat() {
    nBeat++;
    beatDispatcher();
}

void HeartbeatView::makeBeat(string msg) {
    nBeat++;

    this->msg=msg;
    beatDispatcher();
}

void HeartbeatView::onBeat() {
    string beat;

    if(nBeat>4){
        nBeat=0;
    }

    beat= msg;
    for(int i=0; i<4; i++){
        if(i<nBeat)
            beat+=".";
        else
            beat+=" ";
    }

    this->set_text(beat);
}
