#ifndef MISC_GLOBALLOG_H
#define MISC_GLOBALLOG_H

#include <iostream>
#include <fstream>

using namespace std;

class GlobalLog {
public:
    static void Open(string name);
    static void Info(const char* p, ...);
    static void Warning(const char*  p, ...);
    static void Error(const char* p, ...);
    static void Close();
private:
    static ofstream logFile;
};

#endif //MISC_GLOBALLOG_H
