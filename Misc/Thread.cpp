#include "Thread.h"


void Thread::Start() {
    finished=false;
    pthread_create(&threadHandle, nullptr, &Thread::threadExec, this);
}

bool Thread::IsRunning() {
    return !finished;
}

void *Thread::threadExec(void *context) {
    ((Thread*)context)->Run();
    ((Thread*)context)->finished= true;

    return 0;
}

void Thread::Kill() {
    pthread_kill(threadHandle,SIGKILL);
}
