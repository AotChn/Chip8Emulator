#pragma once

#include <SFML/Graphics.hpp>
//#include "color_constants.h"
namespace acGraphics{

const char WINDOW_NAME[] = "CHIP-8";
const double height_width_ratio = .5;
const unsigned int SCREEN_WIDTH = 64 * 25;
const unsigned int SCREEN_HEIGHT = SCREEN_WIDTH * height_width_ratio;



enum CUSTOM_SFEV{
    Idle = -1,
    Draw = sf::Event::EventType::Count,
    
};

};
