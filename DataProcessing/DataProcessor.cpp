#include "DataProcessor.h"

string DataProcessor::buildPath;

void DataProcessor::init(string runPath) {
    size_t lastSlash= runPath.find_last_of('/');
    buildPath= runPath.substr(0, lastSlash);
    buildPath+="/..";
}

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

string DataProcessor::getDataPath() {
    return buildPath+"/data";
}
