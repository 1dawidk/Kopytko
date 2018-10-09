#include "DataProcessor.h"

ofstream DataProcessor::openWriteFile(string path, int mode) {
    ofstream file;

    if(mode==OPEN_FILE_MODE_RELATIVE) {
        file.open(buildPath + path, ios::out | ios::trunc);
    } else {
        char rpath[255];
        realpath(path.c_str(), rpath);
        file.open(rpath, ios::out | ios::trunc);
    }

    return file;
}

ifstream DataProcessor::openReadFile(string path, int mode) {
    ifstream file;

    if(mode==OPEN_FILE_MODE_RELATIVE) {
        file.open(buildPath + path, ios::in);
    } else {
        char rpath[255];
        realpath(path.c_str(), rpath);
        file.open(rpath, ios::in);
    }

    return file;
}

string DataProcessor::getRealPath(string path) {
    return buildPath+path;
}