#ifndef MISC_TALKMANAGER_H
#define MISC_TALKMANAGER_H


#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string.h>

using namespace std;

class TalkManager {
public:
    explicit TalkManager(string path);
    ~TalkManager();

    void Write(string line);
    int Read(string *buff);
    int Read(string *caller, string *cmd, string *data);
private:
    int readLine(string *line);

    fstream streamH;
    long readPos;
    pthread_mutex_t mutex;
};

#endif //MISC_TALKMANAGER_H
