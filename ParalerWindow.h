#pragma once

#include <imgui.h>
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <thread>
#include <mutex>
#include <chrono>
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
            while(!mux.try_lock())std::this_thread::sleep_for(std::chrono::milliseconds(100));
            window.clear();
            window.draw(grayPicture);
            mux.unlock();
            //  Here print pre vie picture


            //
            window.display();
        }
        started = 0;
    }
     void setSprite(sf::Sprite&& sprite)
     {
         if (mux.try_lock()) {
             grayPicture = sprite;
             mux.unlock();
         }
     }
     void checkTerminate()
     {
         if (t1.joinable())
             t1.join();
     }
     std::thread t1;    
     bool started{};
     sf::Sprite grayPicture;
     std::mutex mux;

};