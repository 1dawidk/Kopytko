#ifndef KOPYTKO_ASYNCTASK_H
#define KOPYTKO_ASYNCTASK_H

#include <giomm.h>


template <class inT, class outT>
class AsyncTask {
public:
    AsyncTask();
    void start(inT in);
    void onProgress();
    void onFinished(outT out);

private:
    void work();
    Glib::Thread worker;
    bool workAct;

};


#endif //KOPYTKO_ASYCTASK_H
