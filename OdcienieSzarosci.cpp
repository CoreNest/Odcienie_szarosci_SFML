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

    ParalerWindow win;

    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    sf::err().rdbuf(NULL);

    //allocation of Img, Texture, Sprite and ResultImg
    sf::Image imgPrev;
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
        }
        ImGui::SFML::Update(window, deltaClock.restart());




        // Loading pchoto and counting all color 
        
      

        //Checking user settings changes
        if (UserInterFace::RenderUi()) {
            // kiedy jest zmiana zdj�cia
            if (imgLoader::loaded) {
                imgLoader::loaded = 0;
                imgPrevGray = imgPrev = cutingImg(imgLoader::img);

                baseLookText.loadFromImage(imgLoader::img);
                baseLookSprite = sf::Sprite();
                baseLookSprite.setTexture(baseLookText);
                baseLookSprite.setScale(sf::Vector2f(WINDOW_X / imgLoader::img.getSize().x, WINDOW_Y / imgLoader::img.getSize().y));
            }
            // upewnienie sie ze zdjecie istnieje
            // wyliczanie szarefo zdjecia
            if (imgPrevGray.getSize() != sf::Vector2u(0, 0)) {
                ColorConverter::iterator(imgPrev, imgPrevGray, setting, expandSeting);
                imgTex.loadFromImage(imgPrevGray);                                    // need to cut to the 500 px for prewiev  
                imgSprite.setTexture(imgTex);
                imgSprite.setScale(sf::Vector2f(WINDOW_X / imgPrev.getSize().x, WINDOW_Y / imgPrev.getSize().y));
            }
        }

        bool isHorizontal = false;
        float windowScale = (float)window.getSize().x / window.getSize().y;
        float imgScale = 1;
        if (imgLoader::img.getSize().y != 0) {
            imgScale = (float)imgPrev.getSize().x / imgPrev.getSize().y;
            isHorizontal = windowScale > imgScale;
        }


        //drawing & scaling sprites
        window.clear();
        {

            sf::Sprite disp;
            float spriteScale = imgScale / windowScale;

            if (setting.preView)
            {
                disp = imgSprite;
            }
            else
            {
                disp = baseLookSprite;
            }
            if (isHorizontal) disp.scale(spriteScale, 1);
            else disp.scale(1, 1 / spriteScale);


            window.draw(disp);
        }
        
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

