#include <highgui.h>
#include "ICMWeatherView.h"
#include "UI/UI.h"

vector<string> ICMWeatherView::cityNames;
vector<int> ICMWeatherView::cityX;
vector<int> ICMWeatherView::cityY;

ICMWeatherView::ICMWeatherView(UI *ui) {
    imageUpdateDispatcher.connect(
            sigc::mem_fun(*this, &ICMWeatherView::onImageUpdate));

    curlHandle=curl_easy_init();
    ICMWeatherView::parse(ui);

    this->city=-1;
}

ICMWeatherView::~ICMWeatherView() {
    curl_easy_cleanup(curlHandle);
}

size_t ICMWeatherView::write_data(char *buffer, size_t size, size_t nmemb, void *userp) {
    vector<unsigned char> *stream = (vector<unsigned char>*)userp;
    size_t count = size * nmemb;
    stream->insert(stream->end(), buffer, buffer + count);
    return count;
}

void ICMWeatherView::onImageUpdate() {
    //Decode dowloaded stream
    cv::Mat img= cv::imdecode(stream, -1);

    if(img.rows>0 && img.cols>0) {
        //Resize image to 33% monitor width
        cv::Size s = img.size();
        int w = s.width;
        int x = UI::prcToPix(33, UI_HORIZONTAL);


        float scale = ((float) x) / w;

        cout << "Scale: " << scale << endl;
        cv::resize(img, img, cv::Size(), scale, scale);

        //Write image
        cv::imwrite("icm_image.png", img);

        //Load pixbuf from file
        Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file("icm_image.png");
        this->set(pixbuf);
    }
}

void ICMWeatherView::setCity(string cityName) {
    this->city= findCity(cityName);
}

void ICMWeatherView::refreshWeather() {
    worker->join();
    if(city!=-1) {
        worker = Glib::Thread::create(
                sigc::mem_fun(*this, &ICMWeatherView::work), true);
    }
}

void ICMWeatherView::work() {
    string urlBuilder= "http://www.meteo.pl/um/metco/mgram_pict.php?ntype=0u&fdate=";

    //Append year
    urlBuilder+= to_string(Clock::getYear());

    //Get time
    int month= Clock::getMonth();
    int day= Clock::getDay();
    int hour= Clock::getHour();

    //Append month
    if(month<10)
        urlBuilder+="0";
    urlBuilder+= to_string(month);

    //Append day
    if(hour<7)
        day--;
    if(day<10)
        urlBuilder+="0";
    urlBuilder+= to_string(day);

    //Append hour
    if(hour<7)
        urlBuilder+= "18";
    else if (hour<12)
        urlBuilder+= "00";
    else if (hour<19)
        urlBuilder+= "06";
    else
        urlBuilder+= "12";


    urlBuilder+= "&row="+to_string(cityY[city]);
    urlBuilder+= "&col="+to_string(cityX[city]);
    urlBuilder+= "&lang=pl";

    cout << urlBuilder << endl;

    curl_easy_setopt(curlHandle, CURLOPT_URL, urlBuilder.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, ICMWeatherView::write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &stream);

    curl_easy_perform(curlHandle);
    imageUpdateDispatcher();
}


void ICMWeatherView::parse(UI *ui) {
    ifstream file= ui->openReadFile("/data/cities_latlng", OPEN_FILE_MODE_RELATIVE);

    string line;

    string latd;
    string latm;
    string lngd;
    string lngm;
    string name;

    float lat;
    float lng;
    int x;
    int y;

    getline(file, line);
    getline(file, line);
    getline(file, line);
    while(!line.empty()){
        size_t latStart= line.find_last_of(' ');
        size_t lastW= line.find_last_not_of(' ', latStart);
        size_t lngStart= line.find_last_of(" )", lastW);

        latd= line.substr(latStart+1, 2);
        latm= line.substr(latStart+5, 2);
        lngd= line.substr(lngStart+1, 2);
        lngm= line.substr(lngStart+5, 2);

        lat= stof(latd) + stof(latm)/60;
        lng= stof(lngd) + stof(lngm)/60;
        x= (int)(lng*ICMWEATHERVIEW_X_PARAM_A + ICMWEATHERVIEW_X_PARAM_B);
        y= (int)(lat*ICMWEATHERVIEW_Y_PARAM_C + ICMWEATHERVIEW_Y_PARAM_D);

        lastW= line.find_last_not_of(' ', lngStart);
        name= line.substr(0, lastW+1);
        cityNames.push_back(name);
        cityX.push_back(x);
        cityY.push_back(y);

        getline(file, line);
    }
}

int ICMWeatherView::findCity(string cityName) {
    for(int i=0; i<cityNames.size(); i++){
        if(cityNames[i]==cityName){
            return i;
        }
    }

    return -1;
}


void ICMWeatherView::stop() {
    worker->join();
}
