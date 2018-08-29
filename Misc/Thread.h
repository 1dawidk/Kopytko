#ifndef MISC_THREAD_H
#define MISC_THREAD_H

#include <pthread.h>
#include <sys/signal.h>

class Thread {
public:
    void Start();
    bool IsRunning();
    virtual void Stop()=0;
    void Kill();
protected:
    virtual void Run()=0;

    bool runThread;
    pthread_t threadHandle;
private:
    bool finished;

    static void* threadExec(void *context);
};


#endif //MISC_THREAD_H
