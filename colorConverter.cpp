#include "colorConverter.h"

#define M_PI 3.14159265358979323846

bool ColorConverter::iterator(sf::Image& org, sf::Image& output, Settings& st, ExpandSeting& exSt)
{
	{
		ColorConverter colorConverter(st.RedRatio, st.GreanRatio, st.BlueRatio); //Initializing functor //??Grean
		if (st.hue)
			colorConverter.setBiChrome(st.colDark, st.colBright);

		if (st.expand)
		{
			colorConverter.setKeep(exSt.saveColor,exSt.Ratio);
		}

#pragma omp parallel for
		for (int i{}; i < org.getSize().y; i++)
			for (int j{}; j < org.getSize().x; j++)
				output.setPixel(j, i, colorConverter(org.getPixel(j, i)));

		return true;
	}
	return false;
}

bool ColorConverter::SaveConvImage(sf::Image org, Settings& st, ExpandSeting& exSt)
{
	sf::Image res(org);
	if (!iterator(org, res, st, exSt))
	{
		std::cout << "failed to generate\n\033[1;31mFAIL!!!\033[0m" << std::endl;
		return false;
	}
	std::cout << "successfully generated mono_image, \nstarted saving to file (might take up to 10s)" << std::endl;
	
	if (res.saveToFile(std::string(st.sciezka) + "_mono." + st.items[st.rozszerzenie]))
	{
		std::cout << "saved to :" << std::string(st.sciezka) + "_mono." + st.items[st.rozszerzenie] << "\n\033[1;32mSUCCESS!!!\033[0m" << std::endl;
		return true;
	}
	else
	{
		std::cout << "failed to save\n\033[1;31mFAIL!!!\033[0m" << std::endl;
		return false;
	}
}

ColorConverter::ColorConverter() :
	ColorConverter(1, 1, 1) {}

ColorConverter::ColorConverter(float rW, float gW, float bW) 
	: _redWeight{ rW }, _greenWeight{ gW }, _blueWeight{ bW },
	_isBiCh{ false }, _loColor{ NULL }, _upColor{NULL},
	_isExtend{ false }, _keeptColor{NULL}, _keepRatio{ 1 } {}

ColorConverter::ColorConverter(float rW, float gW, float bW, float* keepCol, float rat)
	: _redWeight{ rW }, _greenWeight{ gW }, _blueWeight{ bW },
	_isBiCh{ false }, _loColor{ NULL }, _upColor{ NULL },
	_isExtend{ true }, _keeptColor{ keepCol }, _keepRatio{ rat } {}

ColorConverter::ColorConverter(float rW, float gW, float bW, float* loCol, float* upCol)
	: _redWeight{ rW }, _greenWeight{ gW }, _blueWeight{ bW },
	_isBiCh{ true }, _loColor{ loCol }, _upColor{ upCol },
	_isExtend{ false }, _keeptColor{ NULL }, _keepRatio{ 1 } {}

ColorConverter::ColorConverter(float rW, float gW, float bW, float* loCol, float* upCol, float* keepCol, float rat)
	: _redWeight{ rW }, _greenWeight{ gW }, _blueWeight{ bW },
		_isBiCh{ true }, _loColor{ loCol }, _upColor{ upCol },
		_isExtend{ true }, _keeptColor{ keepCol }, _keepRatio{ rat } {}

uint8_t inRange(int par)
{
	return (par > 255 ? 255 : (par < 0 ? 0 : par));
}

void ColorConverter::setBiChrome(float* loCol, float* upCol)
{
	_isBiCh = true;
	_loColor = loCol;
	_upColor = upCol;
}

void ColorConverter::setKeep(float* kpCol, float rat)
{
	_isExtend = true;
	_keeptColor = kpCol;
	_keepRatio = rat;
}


/*sf::Color& ColorConverter::GetLinear(sf::Color& inColor)
{
	int linearCol = (inColor.r * _redWeight + inColor.g * _greenWeight + inColor.b * _blueWeight) / (_redWeight + _greenWeight + _blueWeight);
	inColor.r = linearCol;
	inColor.g = linearCol;
	inColor.b = linearCol;
	return inColor;
}*/

inline int biVal(int ln, float& up, float& lo)
{
	return ln * up + lo * (255 - ln);
}

inline float powerer(float _x)
{
	return _x * _x * _x * _x;
}

inline int keepVal(int ln, uint8_t& inC, float& kpV, float& rV)
{
	//return ln + (kpV * (inC - ln)) * rV; // ln <- 255 * kpV
	//return inC - abs(inC - kpV*255) * ((inC - ln) / 255.);
	if ((int)(kpV * 255) == inC) return inC;
	if (rV == 0) return ln;
	return inRange(inC + atan(abs(inC - kpV * 255) * 5 * powerer(1 - rV)) * (ln - inC) / (M_PI / 2) * 1.01);
}

sf::Color ColorConverter::convertToLinear(sf::Color inColor)
{
	int linearCol = (inColor.r * _redWeight + inColor.g * _greenWeight + inColor.b * _blueWeight) / 3;//(_redWeight + _greenWeight + _blueWeight);
	linearCol = inRange(linearCol);
	if(!(_isBiCh || _isExtend)) return sf::Color(linearCol, linearCol, linearCol);

	if (!_isExtend) // if Bichromatic
	{
		return sf::Color(
			biVal(linearCol, _upColor[0], _loColor[0]),//*/linearCol * _upColor[0] + _loColor[0] * (255 - linearCol),
			biVal(linearCol, _upColor[1], _loColor[1]),
			biVal(linearCol, _upColor[2], _loColor[2])
		);
	}
	if (!_isBiCh) // if Extended
	{
		return sf::Color(
			keepVal(linearCol,inColor.r,_keeptColor[0], _keepRatio),//linearCol + (_keeptColor[0] * (inColor.r - linearCol)) * _keepRatio,
			keepVal(linearCol, inColor.g, _keeptColor[1], _keepRatio),
			keepVal(linearCol, inColor.b, _keeptColor[2], _keepRatio)
		);
	}
	// if Bichromatic and Extended
	return sf::Color(
		keepVal(biVal(linearCol, _upColor[0], _loColor[0]), inColor.r, _keeptColor[0], _keepRatio),
		keepVal(biVal(linearCol, _upColor[1], _loColor[1]), inColor.g, _keeptColor[1], _keepRatio),
		keepVal(biVal(linearCol, _upColor[2], _loColor[2]), inColor.b, _keeptColor[2], _keepRatio)
	);
	return inColor;
}