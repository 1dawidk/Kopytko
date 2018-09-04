#ifndef MISC_THREAD_H
#define MISC_THREAD_H

#include <pthread.h>
#include <sys/signal.h>
#include <vector>

class Thread {
public:
    virtual void start();
    virtual void start(int id);
    bool isRunning();
    virtual void stop()=0;
    void kill();
    int getId();


protected:
    virtual void run()=0;

    bool runThread;
    pthread_t threadHandle;
private:
    bool finished;
    int id;

    static void* threadExec(void *context);
    static std::vector<Thread*> threads;
    static Thread* findThreadById(int id);
    static int findThreadPosById(int id);
};


#endif //MISC_THREAD_H
