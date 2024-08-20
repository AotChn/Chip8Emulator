#pragma once

#include <stdint.h>

namespace chip8 {
//===========================================
//	SPECS
//===========================================
//hardare
const unsigned int memorySize = 4096;
const unsigned int registers = 16;
const unsigned int stackSize = 16;
const unsigned int inputSize = 16;
//graphics
const unsigned int maxWidth = 64;
const unsigned int maxHeight = 32;
const unsigned int maxSpriteWidth = 8;
//misc
const unsigned int startAddress = 0x200; //where instructions start in memory
const unsigned int startFont = 0x50; //where font starts in memory
const unsigned int fontsetSize = 80;
const uint8_t fontset[fontsetSize] = {
    0xF0, 0X90, 0X90, 0X90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

//===========================================
//	INSTRUCTION FUNCTIONS
//===========================================

enum INSTR_CODE {
    NIL,
    CLS,            //00E0 : Clear the screen
    RET,            //00EE : Return from a subroutine
    JP_Addr,        //1NNN : Jump to address NNN
    CALL_Addr,      //2NNN : Call subroutine at NNN
    SE_Vx_Byte,     //3XNN : Skip next instruction if Vx == NN
    SNE_Vx_Byte,    //4XNN : Skip next instruction if Vx != NN
    SE_Vx_Vy,       //5XY0 : Skip next instruction if Vx == Vy
    LD_Vx_Byte,     //6XNN : Load NN into Vx
    ADD_Vx_Byte,    //7XNN : Add NN to Vx
    LD_Vx_Vy,       //8XY0 : Load Vy into Vx
    OR_Vx_Vy,       //8XY1 : Set Vx = Vx OR Vy
    AND_Vx_Vy,      //8XY2 : Set Vx = Vx AND Vy
    XOR_Vx_Vy,      //8XY3 : Set Vx = Vx XOR Vy
    ADD_Vx_Vy,      //8XY4 : Set Vx = Vx + Vy, set VF = carry
    SUB_Vx_Vy,      //8XY5 : Set Vx = Vx - Vy, set VF = NOT borrow
    SHR_Vx,         //8XY6 : Set Vx = Vx SHR 1
    SUBN_Vx_Vy,     //8XY7 : Set Vx = Vy - Vx, set VF = NOT borrow
    SHL_Vx,         //8XYE : Set Vx = Vx SHL 1
    SNE_Vx_Vy,      //9XY0 : Skip next instruction if Vx != Vy
    LD_I_Addr,      //ANNN : Load address NNN into I
    JP_V0_Addr,     //BMMM : Jump to address NNN + V0
    RND_Vx_Byte,    //CXNN : Set Vx = random byte AND NN
    DRW_Vx_Vy_Nibble,//DXYN : Draw sprite at (Vx, Vy) with N bytes of sprite data
    SKP_Vx,         //EX9E : Skip next instruction if key with value Vx is pressed
    SKNP_Vx,        //EXA1 : Skip next instruction if key with value Vx is not pressed
    LD_Vx_Delay,    //FX07 : Load delay timer into Vx
    LD_Vx_Key,      //FX0A : Wait for a key press and store it in Vx
    LD_Delay_Vx,    //FX15 : Set delay timer to Vx
    LD_Sound_Vx,    //FX18 : Set sound timer to Vx
    ADD_I_Vx,       //FX1E : Add Vx to I
    LD_F_Vx,        //FX29 : Set I to the location of the sprite for digit Vx
    LD_B_Vx,        //FX33 : Store BCD representation of Vx in memory locations I, I+1, and I+2
    LD_I_Vx,        //FX55 : Store registers V0 to Vx in memory starting at address I
    LD_Vx_I,        //FX65 : Read registers V0 to Vx from memory starting at address I
    LOOKUP_0,       //refer to lookup0
    LOOKUP_E,       //refer to lookupE
    LOOKUP_8,       //refer to lookup8
    LOOKUP_F        //refer to lookupF
    
};


};
