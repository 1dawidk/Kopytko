#ifndef KOPYTKO_ICMWEATHERVIEW_H
#define KOPYTKO_ICMWEATHERVIEW_H

#include <string>
#include <gtkmm/image.h>
#include "curl/curl.h"
#include <vector>
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <iostream>
#include <Logic/Misc/Clock.h>

#define ICMWEATHERVIEW_X_PARAM_A    16.350365
#define ICMWEATHERVIEW_X_PARAM_B    (-93.875912)
#define ICMWEATHERVIEW_Y_PARAM_C    (-24.700071)
#define ICMWEATHERVIEW_Y_PARAM_D    1712.738885


using namespace std;

class UI;

class ICMWeatherView : public Gtk::Image{
public:
    ICMWeatherView(UI *ui);
    ~ICMWeatherView();
    void setCity(string cityName);
    void refreshWeather();

    void onImageUpdate();

    void stop();

    static size_t write_data(char *buffer, size_t size, size_t nmemb, void *userp);

private:
    int city;
    vector<unsigned char> stream;

    Glib::Dispatcher imageUpdateDispatcher;
    Glib::Thread *worker;
    void work();

    CURL  *curlHandle;

    static vector<string> cityNames;
    static vector<int> cityX;
    static vector<int> cityY;
    static void parse(UI *ui);
    static int findCity(string cityName);
};


#endif //KOPYTKO_ICMWEATHERVIEW_H
