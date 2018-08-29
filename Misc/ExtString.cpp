#include "ExtString.h"

queue<string>* ExtString::split(string line, char at) {
    queue<string> *splited=new queue<string>();
    unsigned long lastPos=0;
    unsigned long pos;

    while( (pos=line.find(at, lastPos))!=string::npos ){
        splited->push(line.substr(lastPos, pos-lastPos));
        lastPos= pos+1;
    }

    splited->push(line.substr(lastPos, pos-lastPos));

    return splited;
}

void ExtString::split(string line, char with, vector<string> &buff) {
    unsigned long lastPos=0;
    unsigned long pos;

    buff.clear();

    while( (pos=line.find(with, lastPos))!=string::npos ){
        buff.push_back(line.substr(lastPos, pos-lastPos));
        lastPos= pos+1;
    }

    buff.push_back(line.substr(lastPos, pos-lastPos));
}
