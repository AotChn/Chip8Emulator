#pragma once

#include <stdint.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime> 

#include <deque>

#include "constants.h"
// #include "../graphics/window/window.h"

//left bitshift on first byte to make first byte most signifcant to allow room for second byte
//combine them with OR 
#define BYTES_TO_UINT16(_highByte, _lowByte) (((uint16_t)(_highByte) << 8) | (uint16_t)(_lowByte))
#define PRINT(_toPrint) (std::cout<< _toPrint << std::endl)
//===========================================
//	BIT MASKING MACROS
//===========================================
#define MASK_N000(_16bit)(_16bit >> 12)
#define MASK_0N00(_16bit)((_16bit >> 8) & 0xF)
#define MASK_00N0(_16bit)((_16bit & 0x00F0) >> 4)
#define MASK_000N(_16bit)(_16bit & 0x0F)
#define MASK_00NN(_16bit)((_16bit & 0x00FF))
#define MASK_0NNN(_16bit)(_16bit & 0x0FFF)

namespace chip8{

class Chip {

    typedef int (Chip::*instruction)();

//===========================================
//	LOOKUP TABLES
//===========================================
    instruction lookupGeneral[0xF + 1];
    instruction lookup0[0xE + 1]; //1 and E
    instruction lookupE[0xE + 1]; //A1 and 9E
    instruction lookup8[0xE + 1];
    instruction lookupF[0x65 + 1];

//===========================================
//	INSTRUCTION FUNCTIONS
//===========================================
    int _lookup0();
    int _lookupE();
    int _lookupF();
    int _lookup8();
    int op00E0();
    int op00EE();
    int op1NNN();
    int op2NNN();
    int op3XNN();
    int op4XNN();
    int op5XY0();
    int op6XNN();
    int op7XNN();
    int op8XY0();
    int op8XY1();
    int op8XY2();
    int op8XY3();
    int op8XY4();
    int op8XY5();
    int op8XY6();
    int op8XY7();
    int op8XYE();
    int op9XY0();
    int opANNN();
    int opBNNN();
    int opCXNN();
    int opDXYN();
    int opEX9E();
    int opEXA1();
    int opFX07();
    int opFX0A();
    int opFX15();
    int opFX18();
    int opFX1E();
    int opFX29();
    int opFX33();
    int opFX55();
    int opFX65();
    int opNULL();

//===========================================
//	SPECS
//===========================================
    uint8_t
        frameBuffer[maxWidth][maxHeight],
        mem[memorySize],
        V[registers],
        input[inputSize],
        DT,
        ST,
        SP;

    uint16_t
        stack[stackSize],
        opcode,
        I,
        PC;

public: 

    Chip();
//===========================================
//	INITIALIZING
//===========================================
    int loadROM(const char t_file[]);
    void loadFont();
    void loadLookup();
//===========================================
//	INTERPRET
//===========================================
    uint16_t fetch();
    instruction decode(uint16_t instr);
    instruction decode(bool debug, uint16_t instr);
    int execute(instruction funct);
//===========================================
//  STACK OPERATIONS
//===========================================
    int stackPush(uint16_t item);
    int stackPop();
    uint16_t stackTop();
//===========================================
//	ACCESSOR/MUTATORS
//===========================================
    uint8_t getFrameBuffer(int x, int y){return frameBuffer[x][y];}
    uint16_t getOpcode(){return opcode;}
    void setOpcode(uint16_t t_opcode){opcode = t_opcode;}
    void setInput(uint8_t inpt, uint8_t value) {input[inpt] = value;}
//===========================================
//	TESTING
//===========================================
    void printRegisters();
    void printDebug();
    void printFunctionExecuted(int executeCode);
};

}



/* -------------------------------
    CHIP 8 SPECS 
----------------------------------
4Kib RAM memory 
64x32 monochrome display memory 
16 input keys 

REGISTERS 
    sixteen 8-bit general-purpose : V0 -> VF

SPECIAL REGISTERS
    one 16-bit index : "I"
    one 16-bit program counter : "PC"
    one 8-bit stack pointer : "SP"
    one 8-bit delay timer : "DT"
    one 8-bit sound timer : "ST"
*/

/* MAIN FUNCTION LOOP [check]
    uint16_t fetch() -> instructions come in 2 bytes and we package them as 16bit
    instruction decode(uint16_t) -> take in the opcode and return the operation
    void execute(instruction funct) -> take in the function and operate on the opcode

*/

/* INSTRUCTIONS NEEDED FOR IBM [check]
    00E0 (clear screen)
    1NNN (jump)
    6XNN (set register VX)
    7XNN (add value to register VX)
    ANNN (set index register I)
    DXYN (display/draw)
*/

/* RUN SPACE INVADERS [] */