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

//===========================================
//	STANDARD 
//===========================================
    void attach(Chip* t_chip){chip = t_chip;}
    void onNotify(sf::RenderWindow& window, int event) override;
    void draw(sf::RenderWindow& window);
    bool end();
    void update();
    void enableDebug(){debug=true;}

//===========================================
//	CLASS SPECIFIC 
//===========================================
    void sendInput(int keycode, int value);

};

void Display::onNotify(sf::RenderWindow& window, int event){
	switch (event)
    {
		case acGraphics::CUSTOM_SFEV::Draw:{
            update();
			draw(window);
		    break;
        }

        case sf::Event::KeyPressed:
            sf::Event e;
            sendInput(e.key.code, 1);
            break;

        case sf::Event::KeyReleased:
            sendInput(e.key.code, 0);
            break;

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
            sf::Color toggle = (chip->getFrameBuffer(i, j) == 1) ? ON : OFF;
            rec.setFillColor(toggle);
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
    int e = chip->execute(chip->decode(chip->fetch()));
    if(debug) {
        std::string i="";
        std::cin >> i;
        std::cout << "function executed : ";
        chip->printFunctionExecuted(e);
        chip->printDebug();
    }
}

void Display::sendInput(int keycode, int value) {
    switch(keycode){
        case sf::Keyboard::Num0:
            chip->setInput(0x0 ,value);
            break;
        case sf::Keyboard::Num1:
            chip->setInput(0x1 ,value);
            break;
        case sf::Keyboard::Num2:
            chip->setInput(0x2 ,value);
            break;
        case sf::Keyboard::Num3:
            chip->setInput(0x3 ,value);
            break;
        case sf::Keyboard::Num4:
            chip->setInput(0x4 ,value);
            break;
        case sf::Keyboard::Num5:
            chip->setInput(0x5 ,value);
            break;
        case sf::Keyboard::Num6:
            chip->setInput(0x6 ,value);
            break;
        case sf::Keyboard::Num7:
            chip->setInput(0x7 ,value);
            break;
        case sf::Keyboard::Num8:
            chip->setInput(0x8 ,value);
            break;
        case sf::Keyboard::Num9:
            chip->setInput(0x9 ,value);
            break;
        case sf::Keyboard::A:
            chip->setInput(0xA ,value);
            break; 
        case sf::Keyboard::B:
            chip->setInput(0xB ,value);
            break;
        case sf::Keyboard::C:
            chip->setInput(0xC ,value);
            break;
        case sf::Keyboard::D:
            chip->setInput(0xD ,value);
            break;
        case sf::Keyboard::E:
            chip->setInput(0xE ,value);
            break;
        case sf::Keyboard::F:
            chip->setInput(0xF ,value);
            break;
        default:
            break;
    }
}

};
