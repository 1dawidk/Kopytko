#include "Context.h"


Context::Context() {
}

void Context::init() {

}

void Context::setContextView(Gtk::Box *view) {
    this->add(*view);
}


