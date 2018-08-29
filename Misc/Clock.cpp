
#include "Clock.h"

long Clock::GetTimeMs() {
    milliseconds now=
            duration_cast<milliseconds>(system_clock::now().time_since_epoch());

       return now.count();
}

long Clock::GetTimeS() {
    seconds now=
            duration_cast<seconds>(system_clock::now().time_since_epoch());

    return now.count();
}
