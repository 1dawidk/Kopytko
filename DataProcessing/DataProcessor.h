#ifndef KOPYTKO_DATAPROCESSOR_H
#define KOPYTKO_DATAPROCESSOR_H

#include <fstream>
#include <iostream>

#define OPEN_FILE_MODE_RELATIVE 0
#define OPEN_FILE_MODE_ABSOLUTE 1

using namespace std;

class DataProcessor {
public:
    DataProcessor(string runPath);

    ofstream openWriteFile(string path, int mode);
    ifstream openReadFile(string path, int mode);
    string getRealPath(string path);
private:
    string buildPath;
};


#endif //KOPYTKO_DATAPROCESSOR_H
