#pragma once
#include <string>



struct Settings
{
    //static const std::string  items[]
    static const  char* items[];
    std::string sciezka = { "zjd1" };
    int rozszerzenie;
    float RedRatio=1;
    float BlueRatio=1;
    float GreanRatio=1;
    bool hue;
    bool expand;
    bool preView;
    bool multiWin;
    float colBright[3] ;
    float colDark[3];

    std::string getSciezka(){
        return sciezka + '.' + items[rozszerzenie];
    }
    bool saveSeting();
}static setting;


struct ExpandSeting
{
    float Ratio;
    float saveColor[3];
}static expandSeting;