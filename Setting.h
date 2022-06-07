#pragma once
#include <string>



struct Settings
{
    //static const std::string  items[]
    static const  char* items[];
    std::string sciezka = { "exImage" };
    int rozszerzenie = 1;
    float RedRatio=1;
    float BlueRatio=1;
    float GreanRatio=1;
    bool hue;
    bool expand;
    bool preView;
    bool multiWin;
    float colBright[3] = {1,1,1};
    float colDark[3];

    std::string getSciezka(){
        return sciezka + '.' + items[rozszerzenie];
    }
    bool saveSeting();
}static setting;


struct ExpandSeting
{
    float Ratio=0.73;
    float saveColor[3] = {0.161,0.698,0.1098};
}static expandSeting;