#include "Voice.h"

/************** PUBLICS ****************/
Voice::Voice() {
}

void Voice::init(string voicesDir) {
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
        Log::write("Voice", "Error opening audio: %d", Mix_GetError());
    }
    this->voices_dir= voicesDir;
    if(voices_dir[voicesDir.length()-1]!='/')
        voices_dir+='/';

    queueM= PTHREAD_MUTEX_INITIALIZER;
    this->start();
}

void Voice::say(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buff[512];
    vsprintf(buff, format, args);
    string sentence(buff);
    va_end(args);

    vector<Mix_Music*> *voiceSentence= new vector<Mix_Music*>();

    size_t wcharPos=0;
    size_t lastWcharPos=0;

    while( lastWcharPos!=string::npos ){
        wcharPos= sentence.find_first_of(' ', wcharPos+1);
        string word;

        if(lastWcharPos)
            lastWcharPos++;

        if(wcharPos!=string::npos) {
            word = sentence.substr(lastWcharPos, wcharPos - lastWcharPos);
        } else {
            word = sentence.substr(lastWcharPos);
        }

        voiceSentence->push_back(loadWord(word));

        lastWcharPos= wcharPos;
    }

    //Add to queue
    pthread_mutex_lock(&queueM);
    queue.push_back(voiceSentence);
    pthread_mutex_unlock(&queueM);
}


/************** PRIVATES ****************/
void Voice::saySentence(vector<Mix_Music*> *voiceSentence) {
    for(Mix_Music* m: *voiceSentence){
        if( m != nullptr) {
            Mix_PlayMusic(m, 1);
            while (Mix_PlayingMusic());
        }
    }
}

Mix_Music *Voice::loadWord(string word) {
    string wordPath= dataProcessor->getDataPath()+voices_dir+word+".ogg";
    Mix_Music *m= Mix_LoadMUS(wordPath.c_str());

    return m;
}

void Voice::deleteSentence(vector<Mix_Music*> *voiceSentence) {
    for(Mix_Music *m: *voiceSentence){
        Mix_FreeMusic(m);
    }

    voiceSentence->clear();
}

void Voice::onStart() {
}

void Voice::onRun() {
    if(!queue.empty()){
        vector<Mix_Music*> *sentence;

        //Get sentence sequence
        pthread_mutex_lock(&queueM);
        sentence= queue[0];
        pthread_mutex_unlock(&queueM);

        //Play sentence
        saySentence(sentence);

        //Remove sentence
        deleteSentence(queue[0]);
        delete queue[0];
        pthread_mutex_lock(&queueM);
        queue.erase(queue.begin());
        pthread_mutex_unlock(&queueM);
    } else {
        Thread::pause(200);
    }
}

void Voice::onStop() {
    Log::write("Voice", "Clear memory");
    for(int i=0; i<queue.size(); i++){
        deleteSentence(queue[0]);
        delete queue[0];
        queue.erase(queue.begin());
    }
}
