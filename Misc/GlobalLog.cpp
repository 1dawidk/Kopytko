#include <cstdarg>
#include <cstring>
#include "GlobalLog.h"

ofstream GlobalLog::logFile;

void GlobalLog::Open(const string name) {
    char rpath[256];
    string path= "/var/log/"+name;

    realpath(path.c_str(), rpath);

    logFile.open(rpath, ios::out);

    logFile << "Log ready :)\r\n";
}

void GlobalLog::Info(const char* p, ...) {
    va_list ap;
    va_start(ap, p);
    long len= strlen(p);
    char f[len+7]="Info: ";
    strcat(f, p);

    char buff[1024];
    vsprintf(buff, f, ap);

    logFile << buff;

    va_end(ap);
}

void GlobalLog::Warning(const char* p, ...) {
    va_list ap;
    va_start(ap, p);
    long len= strlen(p);
    char f[len+9]="Warning: ";
    strcat(f, p);

    char buff[1024];
    vsprintf(buff, f, ap);

    logFile << buff;

    va_end(ap);
}

void GlobalLog::Error(const char* p, ...) {
    va_list ap;
    va_start(ap, p);
    long len= strlen(p);
    char f[len+7]="Error: ";
    strcat(f, p);

    char buff[1024];
    vsprintf(buff, f, ap);

    logFile << buff;

    va_end(ap);
}

void GlobalLog::Close() {
    logFile.close();
}
