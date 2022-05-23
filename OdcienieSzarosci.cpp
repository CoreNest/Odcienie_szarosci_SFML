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

int main() {
    ParalerWindow win;
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
    imgPrev.loadFromFile("exImage_res.png");//*************(TO DO) getting std::string of location of file

    sf::Texture imgTex;
    sf::Sprite imgSprite;
    //!!dont work!!("yet")//imgSprite.scale(sf::Vector2f(window.getSize().x / imgPrev.getSize().x, window.getSize().y / imgPrev.getSize().y));

    sf::Image imgPrevGray;
    imgPrevGray.create(imgPrev.getSize().x, imgPrev.getSize().y);

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

        UserInterFace::RenderUi();
        
        win.start();

        ColorConverter::iterator(imgPrev, imgPrevGray, setting, expandSeting);//transforming 

        imgTex.loadFromImage(imgPrevGray);
        imgSprite.setTexture(imgTex);

        window.clear();
        window.draw(imgSprite);
        //window.draw(shape);   //example shapes
        //window.draw(circle4);
        if (!setting.multiWin);// pre view mode per this win draw img with pre vie

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
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
