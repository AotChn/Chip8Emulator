#pragma once

#include "chip.h"
#include "../graphics/window/window.h"


namespace chip8 {

class Display : public acGraphics::Window_Subscriber {
    Chip* chip;
    bool debug = false;

public:
    Display(){}
    ~Display(){}

    void attach(Chip* t_chip){chip = t_chip;}
    void onNotify(sf::RenderWindow& window, int event) override;
    void draw(sf::RenderWindow& window);
    bool end();
    void update();
    void enableDebug(){debug=true;}

};

void Display::onNotify(sf::RenderWindow& window, int event){
	switch (event)
    {
		case acGraphics::CUSTOM_SFEV::Draw:{
            update();
			draw(window);
		    break;
        }
        case acGraphics::CUSTOM_SFEV::Idle:{
            if (end()) {
                window.close();
            }
        } 
    default:
        break;
    }
}

void Display::draw(sf::RenderWindow& window) {
    sf::RectangleShape rec;
    int size = acGraphics::SCREEN_WIDTH/maxWidth;
    rec.setSize(sf::Vector2f(size, size));

    for(int i=0; i<maxWidth; i++) {
        for(int j=0; j<maxHeight; j++) {
            rec.setPosition(sf::Vector2f(i * size, j * size));
            if (chip->getFrameBuffer(i, j) == 1) {
                rec.setFillColor(ON);
            } else {
                rec.setFillColor(OFF);
            }
            window.draw(rec);
        }
    }

}

//manual end trigger 
bool Display::end() {
    if (1!=1) {
        return true;
    }
    return false;
}

void Display::update() {
    if(debug) {
        std::string i="";
        std::cin >> i;
    }
    chip->execute(chip->decode(chip->fetch()));
}

};
