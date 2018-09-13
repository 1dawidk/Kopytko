#include "DebugView.h"

DebugView::DebugView(int maxLines) {
    this->maxLines= maxLines;
    dispatcher.connect(
            sigc::mem_fun(*this, &DebugView::onLog));
}

void DebugView::log(string msg) {
    //If log is to long remove first message
    if(msgs.size()>maxLines){
        msgs.erase(msgs.begin());
    }

    msgs.push_back(msg);

    dispatcher();
}

void DebugView::onLog() {
    string builder;

    for(int i=0; i<msgs.size(); i++){
        builder+=msgs[i];
        builder+="\r\n";
    }

    this->set_text(builder);
}
