#include "Setting.h"
#include <fstream>

using namespace std;

const char* Settings::items[] = { "jpg", "png", "bmp", "png", "tga", "gif", "hdr", "pic" };

bool Settings::saveSeting() {
	fstream plik(setPath, ios::out);
	if (plik.is_open())
	{
		plik << "R:" << RedRatio << endl;
		plik << "B:" << BlueRatio << endl;
		plik << "G:" << GreanRatio << endl;
		
		plik << "hue:" << hue << endl;
		if (hue) {
			plik << "colBright:" << colBright[0] << ' ' << colBright[1] << ' ' << colBright[2] << endl;
			plik << "colDark:" << colDark[0] << ' ' << colDark[1] << ' ' << colDark[2] << endl;
		}
		plik << "expand:" << expand << endl;

		if (expand) {
			plik << "Mixed ratio:" << expandSeting.Ratio << endl;
			plik << "color:" << expandSeting.saveColor[0] << ' ' << expandSeting.saveColor[1] << ' ' << expandSeting.saveColor[2] << endl;
		}
		plik.close();
		return 1;
	}
	return 0;


}
bool Settings::load(ExpandSeting& cos) {
	fstream plik(setPath, ios::in);
	if (plik.is_open())
	{

		string line;
		getline(plik, line, ':');plik>> RedRatio;
		getline(plik, line, ':'); plik >> BlueRatio;
		getline(plik, line, ':'); plik >> GreanRatio;		
		getline(plik, line, ':'); plik >> hue;
		if (hue)
		{
			getline(plik, line, ':');
			plik >>  colBright[0]  >> colBright[1]  >> colBright[2]  ;
			getline(plik, line, ':');
			plik >>  colDark[0]  >> colDark[1]  >> colDark[2]  ;
		}
		getline(plik, line, ':');
		plik  >> expand;
		if (expand) {
			//expandSeting.loading(plik);

			getline(plik, line, ':');
			plik >> cos.Ratio;
			getline(plik, line, ':');
			plik >> cos.saveColor[0] >> cos.saveColor[1] >> cos.saveColor[2];
		}
		plik.close();
		return 1;
	}
}

void ExpandSeting::loading(std::fstream& in)
{
	string line;
	getline(in, line, ':');
	in >> Ratio;
	getline(in, line, ':');
	for (int i{}; i < 3; i++)
	in >> saveColor[i];
}
