#include "colorConverter.h"

colorConverter::colorConverter(float rW, float gW, float bW) 
	: _redWeight{ rW }, _greenWeight{ gW }, _blueWeight{ bW },
	_ishue{ false }, _loColor{ NULL }, _upColor{NULL},
	_isExtend{ false }, _keeptColor{NULL} {}

colorConverter::colorConverter(float rW, float gW, float bW, sf::Color keepCol)
	: _redWeight{ rW }, _greenWeight{ gW }, _blueWeight{ bW },
	_ishue{ false }, _loColor{ NULL }, _upColor{ NULL },
	_isExtend{ true }, _keeptColor{ keepCol } {}

colorConverter::colorConverter(float rW, float gW, float bW, sf::Color loCol, sf::Color upCol)
	: _redWeight{ rW }, _greenWeight{ gW }, _blueWeight{ bW },
	_ishue{ true }, _loColor{ loCol }, _upColor{ upCol },
	_isExtend{ false }, _keeptColor{ NULL } {}

colorConverter::colorConverter(float rW, float gW, float bW, sf::Color loCol, sf::Color upCol, sf::Color keepCol)
	: _redWeight{ rW }, _greenWeight{ gW }, _blueWeight{ bW },
	_ishue{ true }, _loColor{ loCol }, _upColor{ upCol },
	_isExtend{ true }, _keeptColor{ keepCol } {}

sf::Color colorConverter::convertToLInear(sf::Color input)
{
	int gray = (input.r + input.g + input.b) / 3;
	return sf::Color(gray,gray,gray);
}