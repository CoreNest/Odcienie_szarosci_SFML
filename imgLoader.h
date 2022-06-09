#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

class imgLoader
{
public:
	static bool load(std::string&& name)
	{
		if (img.loadFromFile(name)&&!checkFile(name)) {
			std::cout << "Loading " << name << std::endl;
			texture.loadFromImage(img);
			sprite.setTexture(texture);
			loaded = 1;
			name_ = name;
			std::cout << "loaded: " << name << std::endl;
			return 1;
		}
		else
			std::cout << "Error no such file" << std::endl;
		
		return 0;
	}
	static bool checkFile(std::string& name)
	{
		return (name == name_) ? 1 : 0;
	}
	static bool checkFile(std::string&& name)
	{
		return (name == name_) ? 1 : 0;
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
	
	static sf::Image img;
	static bool loaded;
	static sf::Sprite sprite;
private:
	imgLoader();
	static sf::Texture texture;
	static std::string name_;
};


