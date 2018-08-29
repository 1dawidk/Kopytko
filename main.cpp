#include <iostream>
#include "UI/AppMain.h"


int main() {
    auto app= AppMain::create("Kopytko");

    return app->run(*app->getMainWindow());
}