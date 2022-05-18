#pragma once

#include <SFML/Graphics.hpp>

class colorConverter
{
public:
	colorConverter(float rW, float gW, float bW);
	colorConverter(float rW, float gW, float bW, sf::Color keepCol);
	colorConverter(float rW, float gW, float bW, sf::Color loCol, sf::Color upCol);
	colorConverter(float rW, float gW, float bW, sf::Color loCol, sf::Color upCol, sf::Color keepCol);

	sf::Color convertToLInear(sf::Color);
private:
	float _redWeight;
	float _greenWeight;
	float _blueWeight;
	bool _ishue;
	sf::Color _loColor;
	sf::Color _upColor;
	bool _isExtend;
	sf::Color _keeptColor;
};

