#include <cstdarg>
#include <Logic/Misc/Clock.h>
#include "Log.h"

vector<string> Log::msgs;
pthread_mutex_t Log::queueM;

void Log::init() {
    this->start();
}

void Log::write(const char *format, ...) {
    pthread_mutex_lock(&(Log::queueM));
    va_list args;
    va_start(args, format);
    char buff[512];
    sprintf(buff, format, args);


    cout << buff << std::flush;
    pthread_mutex_unlock(&(Log::queueM));
}

void Log::onStart() {

}

void Log::onRun() {
//    pthread_mutex_lock(&(Log::queueM));
//    if(!(Log::msgs).empty()){
//        cout << msgs[msgs.size()-1] << std::flush;
//        msgs.pop_back();
//    }
//    pthread_mutex_unlock(&(Log::queueM));
    Thread::pause(2);
}

void Log::onStop() {
    Log::msgs.clear();
}
