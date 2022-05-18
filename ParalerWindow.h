#pragma once

#include <imgui.h>
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <thread>
#include <iostream>
#include "Setting.h"

class ParalerWindow
{
public:
     void start() {
         
        if (!started&&setting.preView && setting.multiWin)
        {
            if(t1.joinable())
            t1.join();
            t1 = std::thread(&ParalerWindow::loop,this);
            
            started = 1;


        }
    }
     void loop(){      
        sf::RenderWindow window(sf::VideoMode(500, 500), "preView");
        window.setFramerateLimit(60); 
        while (setting.preView && setting.multiWin && window.isOpen()) {
            
            std::cout << t1.get_id()<<std::endl;
            sf::Event event;
            while (window.pollEvent(event)) {
               

                if (event.type == sf::Event::Closed) {
                    window.close();
                    started = 0;
                    setting.multiWin = 0;
                }
            }
            window.clear();
            //window.draw();

            //  Here print pre vie picture


            //
            window.display();
        }
        started = 0;
    }
     void checkTerminate()
     {
         if (t1.joinable())
             t1.join();
     }
     std::thread t1;    
     bool started{};

};