#include <iostream>
#include "src/chip8/app.h"




int main(int argc, char **argv) {
   
   chip8::App Chip8Emulator;
   Chip8Emulator.run("roms/SpaceInvaders.ch8");

   PRINT("runs");
   return 0;
}
