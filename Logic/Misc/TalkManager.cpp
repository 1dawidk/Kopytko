#include "TalkManager.h"
#include "ExtString.h"

TalkManager::TalkManager(string path) {
    streamH.open(path, ios::out | ios::in | ios::trunc);
    readPos=0;
    mutex=PTHREAD_MUTEX_INITIALIZER;
}

TalkManager::~TalkManager() {
    streamH.close();
}

void TalkManager::Write(string line) {
    pthread_mutex_lock(&mutex);

    streamH.seekp(0, ios::end);
    streamH << line << endl;

    pthread_mutex_unlock(&mutex);
}

int TalkManager::Read(string *buff) {
    int len=0;

    pthread_mutex_lock(&mutex);

    streamH.seekg(readPos);
    if(getline(streamH, *buff)){
        readPos= streamH.tellg();
        len= (int)strlen((const char*)buff);
    }
    streamH.clear(ios::goodbit);

    pthread_mutex_unlock(&mutex);

    return len;
}

int TalkManager::Read(string *caller, string *cmd, string *data) {
    string talkLine;

    *caller= "";
    *cmd= "";
    *data= "";

    if(readLine(&talkLine)) {
        unsigned long posCmd=talkLine.find('|');
        unsigned long posData=talkLine.find('|',posCmd+1);

        if(posCmd!=string::npos){
            *caller= talkLine.substr(0, posCmd);

            if(posData!=string::npos) {
                *cmd = talkLine.substr(posCmd + 1, posData - posCmd - 1);
                *data= talkLine.substr(posData+1, talkLine.length()-posData);
            } else
                *cmd= talkLine.substr(posCmd+1, talkLine.length()-posCmd);
        }
    }

    if(!(caller->empty() || cmd->empty()))
        return 1;
    else
        return 0;
}

int TalkManager::readLine(string *line) {
    int len=0;

    pthread_mutex_lock(&mutex);

    streamH.seekg(readPos);
    if(getline(streamH, *line)){
        readPos= streamH.tellg();
        len= (int)strlen((const char*)line);
    }
    streamH.clear(ios::goodbit);

    pthread_mutex_unlock(&mutex);

    return len;
}
