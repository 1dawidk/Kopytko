#ifndef KOPYTKO_DATAPROCESSOR_H
#define KOPYTKO_DATAPROCESSOR_H

#include <fstream>
#include <iostream>

#define OPEN_FILE_MODE_RELATIVE 0
#define OPEN_FILE_MODE_ABSOLUTE 1

using namespace std;

class DataProcessor {
public:
    static void init(string runPath);

    static ofstream openWriteFile(string path, int mode);
    static ifstream openReadFile(string path, int mode);
    static string getRealPath(string path);
    static string getDataPath();
private:
    static string buildPath;
};


#endif //KOPYTKO_DATAPROCESSOR_H
