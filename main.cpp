#include <iostream>
#include "src/app/app.h"




int main(int argc, char **argv) {
   
   App Chip8Emulator;
   Chip8Emulator.run("roms/IBM_Logo.ch8");

   PRINT("runs");
   return 0;
}
