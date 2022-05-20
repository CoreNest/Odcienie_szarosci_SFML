#include "colorConverter.h"

bool ColorConverter::iterator(sf::Image& org, sf::Image& output, Settings& st, ExpandSeting& exSt)
{
	if (st.preView)
	{
		ColorConverter colorConverter(st.RedRatio, st.GreanRatio, st.BlueRatio); //Initializing functor //??Grean
		if (st.hue)
			colorConverter.setBiChrome(st.colDark, st.colBright);

		if (st.expand)
		{
			float tmp[] = { 0,1,0 };
			colorConverter.setKeep(exSt.saveColor,exSt.Ratio);
		}

		for (unsigned int i{}; i < org.getSize().y; i++)
			for (unsigned int j{}; j < org.getSize().x; j++)
				output.setPixel(j, i, colorConverter(org.getPixel(j, i)));

		return true;
	}
	output = org;
	return false;
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


sf::Color& ColorConverter::GetLinear(sf::Color& inColor)
{
	int linearCol = (inColor.r * _redWeight + inColor.g * _greenWeight + inColor.b * _blueWeight) / (_redWeight + _greenWeight + _blueWeight);
	inColor.r = linearCol;
	inColor.g = linearCol;
	inColor.b = linearCol;
	return inColor;
}

inline int biVal(int ln, float& up, float& lo)
{
	return ln * up + lo * (255 - ln);
}

inline int keepVal(int ln, uint8_t& inC, float& kpV, float& rV) // NEED A LITTLE BIT OF ADDITIONAL WORK !!!!!!!!!!
{
	return ln + (kpV * (inC - ln)) * rV;
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
	return sf::Color(
		keepVal(biVal(linearCol, _upColor[0], _loColor[0]), inColor.r, _keeptColor[0], _keepRatio),
		keepVal(biVal(linearCol, _upColor[1], _loColor[1]), inColor.g, _keeptColor[1], _keepRatio),
		keepVal(biVal(linearCol, _upColor[2], _loColor[2]), inColor.b, _keeptColor[2], _keepRatio)
	);
	return inColor;
}