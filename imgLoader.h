#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

class imgLoader
{
public:
	bool load(std::string&& name)
	{
		name = "zdj1.png";
		if (img.loadFromFile(name)) {
			std::cout << "³adowanie " << name << std::endl;
			text.create(img.getSize().x, img.getSize().y);
			text.update(img);
			sprite.setTexture(text);
			sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
			loaded = 1;
			return 1;
		}
		
		return 0;
	}
	/*bool load(std::string& name)
	{
		
		if (img.loadFromFile(name)) {
			std::cout << "³adowanie " << name << std::endl;
			text.create(800, 600);
			text.loadFromImage(img,sf::IntRect(0,0,800,600));
			square.setTexture(&text);
			square.setSize(sf::Vector2f(text.getSize().x, text.getSize().y));
			loaded = 1;
			return 1;
		}
		return 0;
	}*/
	std::string name_;
	sf::Image img;
	sf::Texture text;
	sf::RectangleShape square ;
	sf::Sprite sprite;
	bool loaded{};
}static loader;

