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

#define WINDOW_X 1300.
#define WINDOW_Y 600.

sf::Image cutingImg(sf::Image& img, int maxSize = 500)
{
    double z = (img.getSize().x > img.getSize().y) ? img.getSize().x : img.getSize().y;
    sf::Image small;

    if (z) {
        z = maxSize / z;
        small.create(img.getSize().x * z, img.getSize().y * z);
        z = 1 / z;
        for (int i{}; i < small.getSize().x; i++)
        {
            for (int j{}; j < small.getSize().y; j++)
                small.setPixel(i, j, img.getPixel(i * z, j * z));
        }
    }
    return small;

}

int main() {
    //ParalerWindow win;
    //bool forConverter{};
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    sf::err().rdbuf(NULL);

    //allocation of Img, Texture, Sprite and ResultImg
    sf::Image imgPrev;
    //imgPrev.loadFromFile("zdj1.png");//*************(TO DO) getting std::string of location of file

    sf::Texture imgTex;
    sf::Sprite imgSprite;
    sf::Texture baseLookText;
    sf::Sprite baseLookSprite;

    sf::Image imgPrevGray;

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized)
            {
                sf::Vector2u ss = window.getSize();
                sf::Vector2f s = sf::Vector2<float>(ss);
                double co = ((s.x - 00) / imgPrev.getSize().x < (s.y / imgLoader::img.getSize().y)) ? (s.x - 00) / imgLoader::img.getSize().x : s.y / imgLoader::img.getSize().y;
                baseLookSprite.setScale(sf::Vector2f(co, co));
                co = ((s.x - 00) / imgPrev.getSize().x < (s.y / imgPrev.getSize().y)) ? (s.x - 00) / imgPrev.getSize().x : s.y / imgPrev.getSize().y;
                imgSprite.setScale(sf::Vector2f(co, co));
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());



        // Loading pchoto and counting all color 
        
      
        //Checking user settings changes
        if (UserInterFace::RenderUi()) {
            // kiedy jest zmiana zdjêcia
            if (imgLoader::loaded) {
                imgLoader::loaded = 0;
                imgPrevGray = imgPrev = cutingImg(imgLoader::img);

                //window.setSize(imgLoader::img.getSize());
                baseLookText.loadFromImage(imgLoader::img);// orginal photo show not cutted one !!!!!
                baseLookSprite = sf::Sprite();
                baseLookSprite.setTexture(baseLookText);
                sf::Vector2u ss = window.getSize();
                sf::Vector2f s = sf::Vector2<float>(ss);
                double co = ((s.x) / imgPrev.getSize().x < (s.y / imgLoader::img.getSize().y)) ? (s.x) / imgLoader::img.getSize().x : s.y / imgLoader::img.getSize().y;
                baseLookSprite.setScale(sf::Vector2f(co, co));
                //forConverter = 1;
            }
            // upewnienie sie ze zdjecie istnieje
            // wyliczanie szarefo zdjecia
            if (imgPrevGray.getSize() != sf::Vector2u(0, 0)) {
                ColorConverter::iterator(imgPrev, imgPrevGray, setting, expandSeting);//transforming in full scale 
                imgTex.loadFromImage(imgPrevGray);                                    // need to cut to the 500 px for prewiev  
                imgSprite.setTexture(imgTex);
                sf::Vector2u ss = window.getSize();
                sf::Vector2f s = sf::Vector2<float>(ss);
                double co = ((s.x - 00) / imgPrev.getSize().x < (s.y / imgPrev.getSize().y)) ? (s.x - 00) / imgPrev.getSize().x : s.y / imgPrev.getSize().y;
                imgSprite.setScale(sf::Vector2f(co, co));
            }
        }


        //drawing & scaling sprites
        window.clear();
        {
            sf::Sprite* disp;
            if (setting.preView)
            {
                disp = &imgSprite;
            }
            else
            {
                disp = &baseLookSprite;
            }
            window.draw(*disp);
        }


        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    //win.checkTerminate();
}

