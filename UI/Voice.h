#ifndef KOPYTKO_VOICE_H
#define KOPYTKO_VOICE_H

#include <dkulpaclibs/misc/debug/Log.h>
#include <dkulpaclibs/misc/Thread.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>
#include <DataProcessing/DataProcessor.h>

using namespace std;

class Voice : public Thread {
public:
    Voice();
    void init(string voicesDir);
    void say(const char *format, ...);

protected:
    void onStart() override;

    void onRun() override;

    void onStop() override;

private:

    Mix_Music* loadWord(string word);
    void saySentence(vector<Mix_Music*> *voiceSentence);
    void deleteSentence(vector<Mix_Music*> *voiceSentence);

    string voices_dir;
    DataProcessor *dataProcessor;
    vector<vector<Mix_Music*>*> queue;
    pthread_mutex_t queueM;

};


#endif //KOPYTKO_VOICE_H
