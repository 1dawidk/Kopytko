#ifndef MISC_EXTSTRING_H
#define MISC_EXTSTRING_H

#include <string>
#include <queue>

using namespace std;

    class ExtString {
    public:
        static queue<string>* split(string line, char at);
        static void split(string line, char with, vector<string> &buff);
    };


#endif //MISC_EXTSTRING_H
