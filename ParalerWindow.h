#pragma once

#include <imgui.h>
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <thread>

#include "Setting.h"

class ParalerWindow
{
public:
     void start() {
        if (setting.preView && setting.multiWin)
        {
            *t1 = std::thread(&ParalerWindow::loop,this);

        }
    }
     void loop(){      
        sf::RenderWindow window(sf::VideoMode(500, 500), "preView");
        window.setFramerateLimit(60); 
        while (setting.preView && setting.multiWin) {
            window.clear();
            //window.draw();
           
            window.display();
        }
        ImGui::SFML::Shutdown();
    }
     std::thread* t1;     

};