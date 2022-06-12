#pragma once

#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Setting.h"

class ColorConverter
{
public:
	ColorConverter();
	ColorConverter(float rW, float gW, float bW);
	ColorConverter(float rW, float gW, float bW, float* keepCol, float rat);
	ColorConverter(float rW, float gW, float bW, float* loCol, float* upCol);
	ColorConverter(float rW, float gW, float bW, float* loCol, float* upCol, float* keepCol, float rat);

	void setBiChrome(float* loCol, float* upCol);
	void setKeep(float* kpCol, float rat);

	//sf::Color& GetLinear(sf::Color&);
	sf::Color convertToLinear(sf::Color);
	sf::Color operator()(sf::Color col) {  return convertToLinear(col); }

	static bool iterator(sf::Image& org, sf::Image& output, Settings& st, ExpandSeting& exSt);

	static bool SaveConvImage(sf::Image org, Settings& st, ExpandSeting& exSt, std::string path);

private:
	float _redWeight;
	float _greenWeight;
	float _blueWeight;
	bool _isBiCh;
	float* _loColor;
	float* _upColor;
	bool _isExtend;
	float* _keeptColor;
	float _keepRatio;
};

