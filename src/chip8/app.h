#pragma once

#include "../graphics/window/window.h"
#include "../chip8/chip.h"
#include "../chip8/display.h"

namespace chip8 {
class App {
   acGraphics::Window window;
   Display display;
   Chip chip;


public:
    App(){};

    void run(){
      char* rom = "";
      std::cout<< "enter rom path: ";
      std::cin >> rom;
      chip.loadROM(rom);
      display.attach(&chip);
      window.attach(&display);
      window.run();
    }

    void run(char* rom){
      chip.loadROM(rom);
      display.enableDebug();
      display.attach(&chip);
      window.attach(&display);
      window.run();
    }

};

}
