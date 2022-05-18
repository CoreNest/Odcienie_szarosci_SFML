#include "Setting.h"
#include <fstream>

using namespace std;

const char* Settings::items[] = { "jpg", "png", "bmp", "png", "tga", "gif", "hdr", "pic" };

bool Settings::saveSeting() {
	fstream plik("settings.txt", ios::out);
	if (plik.is_open())
	{
		plik << "R:" << RedRatio << endl;
		plik << "B:" << BlueRatio << endl;
		plik << "G:" << GreanRatio << endl;
		plik << "hue:" << hue << endl;
		plik << "Mixed ratio" << expandSeting.Ratio << endl;
		plik << "color" << expandSeting.saveColor << endl;

		plik.close();
		return 1;
	}
	return 0;


}