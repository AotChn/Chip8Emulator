#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../constants.h"
#include "../color_constants.h"
#include "window_observer.h"

namespace acGraphics{
class Window: public Window_Publisher {
    
    sf::RenderWindow window;
    
public: 
    Window();
    void run();
    void draw();
    void render();
    void update();
    void process_events();
    void close();
    void close(bool);

}; 

}
