#pragma once 

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../observer/observer.h"

namespace acGraphics{
class Window_Subscriber : public Subscriber {
    public: 
        virtual ~Window_Subscriber(){}
        
        virtual void onNotify(sf::RenderWindow& window, int event) {
            if (_debug) {
                std::printf("[WObserver%d] : onNotify!\n", _id);    
            } 
        }
};

class Window_Publisher : public Publisher {
    public:
        virtual ~Window_Publisher(){}

        virtual void Notify(sf::RenderWindow& window, int event) {
            if (_debug) {
                print_sub();
            }
            auto cur = _head;
            while (cur != nullptr) {
                auto sub = cur->_data;
                static_cast<Window_Subscriber*>(sub)->onNotify(window, event);
                cur = cur->_next;
            }
        }
};

};