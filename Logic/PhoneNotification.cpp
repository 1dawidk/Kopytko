#include "PhoneNotification.h"

PhoneNotification *PhoneNotification::newInstance(const string postPairs) {
    PhoneNotification *phoneNotification= new PhoneNotification();

    PostPairs pp(postPairs);
    string val;

    phoneNotification->from= NOTIFICATION_FROM_PHONE;

    if(pp.getString("app", val)==PostPairs::key_found)
        phoneNotification->appName= val;
    else
        return NULL;

    if(pp.getString("text", val)==PostPairs::key_found)
        phoneNotification->text= val;
    else
        return NULL;

    if(pp.getString("title", val)==PostPairs::key_found)
        phoneNotification->title= val;
    else
        return NULL;

    return phoneNotification;
}

string PhoneNotification::getAppName(){
    return appName;
}

string PhoneNotification::getTitle(){
    return appName+": "+title;
}