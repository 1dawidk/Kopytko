#include "Thread.h"


std::vector<Thread*> Thread::threads;

void Thread::start() {
    finished=false;
    id=threads.size();
    threads.push_back(this);
    pthread_create(&threadHandle, nullptr, &Thread::threadExec, this);
}

void Thread::start(int id){
    finished= false;
    this->id= id;
    threads.push_back(this);
    pthread_create(&threadHandle, nullptr, &Thread::threadExec, this);
}

bool Thread::isRunning() {
    return !finished;
}

void* Thread::threadExec(void *context) {
    ((Thread*)context)->run();
    ((Thread*)context)->finished= true;

    return 0;
}

void Thread::kill() {
    pthread_kill(threadHandle,SIGKILL);
}

int Thread::getId() {
    return id;
}

Thread* Thread::findThreadById(int id) {
    for(int i=0; i<Thread::threads.size(); i++){
        if(Thread::threads[i]->getId()==id)
            return Thread::threads[i];
    }

    return nullptr;
}

int Thread::findThreadPosById(int id) {
    for(int i=0; i<Thread::threads.size(); i++){
        if(Thread::threads[i]->getId()==id)
            return Thread::threads[i]->getId();
    }

    return -1;
}