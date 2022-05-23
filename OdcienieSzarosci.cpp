// OdcienieSzarosci.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define SFML_Proj

#include <imgui.h>
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "UserInterFace.h"
#include "ParalerWindow.h"
#include "ColorConverter.h"
#include "ImgLoader.h"


int main() {
    ParalerWindow win;
    bool forConverter{};
    sf::RenderWindow window(sf::VideoMode(800, 600), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    /*sf::Clock clock;
    sf::Time time = sf::Time::Zero;
    unsigned int FPS = 0, frame_counter = 0;
    sf::Text fps_text;*/ //fps counter part 1 (part 2 also must be uncommented to work)

    //examples of shapes (***CAN BE DELEATED***)
    /*sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);*/

    /*sf::VertexArray circle4(sf::TriangleStrip, 512);
    sf::Vector2f pos4(300, 330);
    int radius = 125;

    for (int i = 0; i < 256; i++)
    {
        circle4[i * 2].position = pos4 + sf::Vector2f(cos(3.14159 * i / 127) * radius, -sin(3.14159 * i / 127) * radius);
        circle4[i * 2].color = sf::Color(255, i, 1 * 255 / 100);

        circle4[i * 2 + 1].position = pos4;
        circle4[i * 2 + 1].color = sf::Color(0, i, 1 * 255 / 100);
    }*/

    //allocation of Img, Texture, Sprite and ResultImg
    sf::Image imgPrev;
    //imgPrev.loadFromFile("zdj1.png");//*************(TO DO) getting std::string of location of file

    sf::Texture imgTex;
    sf::Sprite imgSprite;
    sf::Texture baseLookText;
    sf::Sprite baseLookSprite;
    //!!dont work!!("yet")//imgSprite.scale(sf::Vector2f(window.getSize().x / imgPrev.getSize().x, window.getSize().y / imgPrev.getSize().y));

    sf::Image imgPrevGray;
    

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        if (UserInterFace::RenderUi()) {        
                
            
            if (imgLoader::loaded) {
                imgLoader::loaded = 0;
                imgPrevGray=imgPrev = sf::Image(imgLoader::img);
                
                
                baseLookText.loadFromImage(imgPrev);
                baseLookSprite.setTexture(baseLookText);
                forConverter = 1;
            } 
            if (imgPrevGray.getSize() != sf::Vector2u(0, 0)) {
                ColorConverter::iterator(imgPrev, imgPrevGray, setting, expandSeting);//transforming 
                imgTex.loadFromImage(imgPrevGray);
                imgSprite.setTexture(imgTex);
            }
            
        }

        window.clear();
        
        {
            if (setting.preView)
                window.draw(imgSprite);
            else
                window.draw(baseLookSprite);
        }
        //window.draw(circle4);
        // pre view mode per this win draw img with pre vie

        /*if (clock.getElapsedTime().asSeconds() >= 1.0f)
        {
            FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
            clock.restart();
            frame_counter = 0;
            window.setTitle(std::to_string(FPS));
        }
        frame_counter++;*/ //fps counter part 2 (part 1 also must be uncommented to work)

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    win.checkTerminate();
}

