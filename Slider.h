#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Slider : public sf::Drawable
{
public:
	~Slider() { delete toLoad; };
	Slider() :Slider(10, 10, 150, 30, 10, sf::Color::Black, sf::Color::White) {}

	//Slider(int px, int py, int sx, int sy) : Slider(px, py, sx, sy, sy / 6, sf::Color::Black, sf::Color::White) {}

	Slider(int px, int py, int sx, int sy, sf::Color begColor= sf::Color::Black, sf::Color endColor= sf::Color::White) : Slider(px, py, sx, sy, sy / 6, begColor, endColor) {}

	Slider(sf::Vector2i position, sf::Vector2i size = sf::Vector2i(100, 20), sf::Color begColor = sf::Color::Black, sf::Color endColor = sf::Color::White)
		: Slider(position.x, position.y, size.x, size.y, begColor, endColor)	{};

	Slider(int px, int py, int sx, int sy, int lT, sf::Color begColor, sf::Color endColor)
	{
		value = 0;
		freeZone = 2;
		flag = false;

		lineThick = lT;
		rectWidth = sx / 10;

		position = sf::Vector2f(px, py);
		size = sf::Vector2f(sx, sy);

		lnColor = sf::Color::White;
		rcColor = sf::Color::White;

		rect.setSize(sf::Vector2f(rectWidth, size.y));
		rect.setFillColor(rcColor);
		rect.setOutlineColor(rcColor);
		rect.setOutlineThickness(1.0f);
		rect.setPosition(sf::Vector2f(position.x + freeZone + (value*((size.x - rectWidth) - freeZone * 2) / 100), position.y));

		line.setSize(sf::Vector2f(size.x, lineThick));
		line.setFillColor(lnColor);
		line.setOutlineColor(lnColor);
		line.setOutlineThickness(1.0f);
		line.setPosition(sf::Vector2f(position.x, position.y + (sy - lineThick) / 2));

		vertexToRectangle(px, py, sx, sy, lT, begColor, endColor);
		
	}

	sf::RectangleShape rect;
	sf::RectangleShape line;
	//sf::RectangleShape rect;

	sf::Vector2f position;
	sf::Vector2f size;

	int lineThick;
	int rectWidth;
	int freeZone;

	sf::Color lnColor;
	sf::Color rcColor;

	double value;
	bool flag;

	void setValue(int v)
	{
		value = v;
		rect.setPosition(sf::Vector2f(position.x + freeZone + (value*((size.x - rectWidth) - freeZone * 2) / 100), position.y));
	}
	void setLineThick(int v)
	{
		lineThick = v;
		line.setSize(sf::Vector2f(size.x, lineThick));
		line.setPosition(sf::Vector2f(position.x, position.y + (size.y - lineThick) / 2));
		//rainbow[0].position = sf::Vector2f(position.x, position.y + (size.y - lineThick) / 2);
		//rainbow[1].position = sf::Vector2f(position.x + size.x, position.y + (size.y - lineThick) / 2);
		//rainbow[2].position = sf::Vector2f(position.x + size.x, position.y + (size.y - lineThick) / 2 + lineThick);
		//rainbow[3].position = sf::Vector2f(position.x, position.y + (size.y - lineThick) / 2 + lineThick);
	}
	void setRectWidth(int v)
	{
		rectWidth = v;
		rect.setSize(sf::Vector2f(rectWidth, size.y));
	}

	void set(sf::Event &event)
	{
		int mouseX, mouseY;
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			mouseX = event.mouseButton.x - position.x;
			mouseY = event.mouseButton.y - position.y;
			if (0 < mouseX && mouseX < size.x && 0 < mouseY && mouseY < size.y)
			{
				flag = true;
			}
		}
		else if (event.type == sf::Event::MouseMoved && flag)
		{
			mouseX = event.mouseMove.x - position.x;

			value = mouseX * 100 / (size.x - rectWidth - freeZone) - rectWidth / 4 + freeZone;

			if (value < 0) value = 0;
			if (value > 100) value = 100;
			//std::cout << mouseX << "\n";
		}
		else if (event.type == sf::Event::MouseButtonReleased && flag)
		{
			flag = false;
		}
		//std::cout << value << "\n";

		if (flag) rect.setPosition(sf::Vector2f(position.x + freeZone + (value*((size.x - rectWidth) - freeZone * 2) / 100), position.y));

	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(line);
		//target.draw(rainbow);
		target.draw(rect);
	}
	private:
		sf::Texture* toLoad;
		/// <summary>
		/// creat texter using color and updating it to rectangle
		/// </summary>
		/// <param name="px"></param>
		/// <param name="py"></param>
		/// <param name="sx"></param>
		/// <param name="sy"></param>
		/// <param name="lT"></param>
		/// <param name="begColor">left side color</param>
		/// <param name="endColor">right side color</param>
		void vertexToRectangle(int px, int py, int sx, int sy, int lT, sf::Color begColor, sf::Color endColor)
		{	
			sf::VertexArray rainbow;

			rainbow = sf::VertexArray(sf::Quads, 4);
			rainbow[0].position = sf::Vector2f(px, py + (sy - lineThick) / 2);
			rainbow[1].position = sf::Vector2f(px + sx, py + (sy - lineThick) / 2);
			rainbow[2].position = sf::Vector2f(px + sx, py + (sy - lineThick) / 2 + lineThick);
			rainbow[3].position = sf::Vector2f(px, py + (sy - lineThick) / 2 + lineThick);

			rainbow[0].color = begColor;
			rainbow[1].color = endColor;
			rainbow[2].color = endColor;
			rainbow[3].color = begColor;

			toLoad = new sf::Texture;
			sf::RenderTexture texture_r;
			texture_r.create(size.x,size.y);//seting size
			toLoad->create(size.x, size.y);
			texture_r.draw(rainbow);
			toLoad->update(texture_r.getTexture());
			rect.setTexture(toLoad);
		}
};

