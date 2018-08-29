#ifndef MISC_CLOCK_H
#define MISC_CLOCK_H

#include <chrono>

using namespace std::chrono;

class Clock {
public:
    static long GetTimeMs();
    static long GetTimeS();
};


#endif //MISC_CLOCK_H
