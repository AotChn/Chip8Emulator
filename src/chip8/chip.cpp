#include "chip.h"

namespace chip8{

//===========================================
//	INITIALIZING
//===========================================

Chip::Chip() {
    PC = startAddress;
    I = startAddress;
    SP = 0x0;
    srand(time(0));
    std::fill(std::begin(V), std::end(V), 0);
    std::fill(std::begin(stack), std::end(stack), 0);
    std::fill(std::begin(input), std::end(input), 0);
    std::fill(std::begin(mem), std::end(mem), 0);
    loadFont();
    loadLookup();
    op00E0();
};

void Chip::loadLookup() {
    //ik this waste space but whatever
    //max index 0xE
    for(int i=0; i<0xE; i++) {
        lookup0[i] = &Chip::opNULL;
        lookupE[i] = &Chip::opNULL;
        lookup8[i] = &Chip::opNULL;
    }
    //max index 0x65
    for(int i=0; i<0x65; i++) {
        lookupF[i] = &Chip::opNULL;
    }
    //general set
    lookupGeneral[0x0] = &Chip::_lookup0; //refer lookup0
    lookupGeneral[0x1] = &Chip::op1NNN;
    lookupGeneral[0x2] = &Chip::op2NNN;
    lookupGeneral[0x3] = &Chip::op3XNN;
    lookupGeneral[0x4] = &Chip::op4XNN;
    lookupGeneral[0x5] = &Chip::op5XY0;
    lookupGeneral[0x6] = &Chip::op6XNN;
    lookupGeneral[0x7] = &Chip::op7XNN;
    lookupGeneral[0x8] = &Chip::_lookup8; //refer lookup8
    lookupGeneral[0x9] = &Chip::op9XY0;
    lookupGeneral[0xA] = &Chip::opANNN;
    lookupGeneral[0xB] = &Chip::opBNNN;
    lookupGeneral[0xC] = &Chip::opCXNN;
    lookupGeneral[0xD] = &Chip::opDXYN;
    lookupGeneral[0xE] = &Chip::_lookupE; //refer lookupE
    lookupGeneral[0xF] = &Chip::_lookupF; //refer lookupF
    //0 set
    lookup0[0x0] = &Chip::op00E0;
    lookup0[0xE] = &Chip::op00EE;
    //E set
    lookupE[0x1] = &Chip::opEXA1;
    lookupE[0xE] = &Chip::opEX9E;
    //8 set
    lookup8[0x0] = &Chip::op8XY0;
    lookup8[0x1] = &Chip::op8XY1;
    lookup8[0x2] = &Chip::op8XY2;
    lookup8[0x3] = &Chip::op8XY3;
    lookup8[0x4] = &Chip::op8XY4;
    lookup8[0x5] = &Chip::op8XY5;
    lookup8[0x6] = &Chip::op8XY6;
    lookup8[0x7] = &Chip::op8XY7;
    lookup8[0xE] = &Chip::op8XYE;
    //F set
    lookupF[0x07] = &Chip::opFX07;
    lookupF[0x0A] = &Chip::opFX0A;
    lookupF[0x15] = &Chip::opFX15;
    lookupF[0x18] = &Chip::opFX18;
    lookupF[0x1E] = &Chip::opFX1E;
    lookupF[0x29] = &Chip::opFX29;
    lookupF[0x33] = &Chip::opFX33;
    lookupF[0x55] = &Chip::opFX55;
    lookupF[0x65] = &Chip::opFX65;
}

int Chip::loadROM(const char t_file[]) {

    std::ifstream file;
    //opens file in binary and at the end 
    file.open(t_file, std::ios::binary | std::ios::ate);

    if(!file) {
        std::cout<< "file: " << t_file << " | opening failed \n";
        return 1;
    }

    std::streampos size = file.tellg();

    if(size > (0xFFF - 0x200)) {
        std::cout<< "instruction file too large \n";
        return 2;
    }

    char* buffer = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    for (int i=0; i<size; i++) {
        mem[startAddress + i] = buffer[i];
    }

    delete[] buffer;

    I = 0x200;
    return 0;

};

void Chip::loadFont() {
    for(int i=0; i<fontsetSize; i++) {
        mem[startFont + i] = fontset[i];
    }
}

//===========================================
//	INSTRUCTION FUNCTIONS
//===========================================

int Chip::opNULL() {
    PRINT("instructions NOT found");
    return NIL;
}

int Chip::_lookup0() {
    uint8_t forth = MASK_000N(opcode);
    return ((*this).*(lookup0[forth]))();
}

int Chip::_lookupE(){
    uint8_t third = MASK_00N0(opcode);
    uint8_t forth = MASK_000N(opcode);
    uint8_t byte = (third << 4) | forth;
    return ((*this).*(lookup8[byte]))();
}

int Chip::_lookupF(){
    uint8_t third = MASK_00N0(opcode);
    uint8_t forth = MASK_000N(opcode);
    uint8_t byte = (third << 4) | forth;
    return ((*this).*(lookupF[byte]))();

}

int Chip::_lookup8(){
    uint8_t forth = MASK_000N(opcode);
    return ((*this).*(lookup8[forth]))();
}

int Chip::op00E0(){
    for(int i=0; i<maxWidth; i++) {
        for(int j=0; j<maxHeight; j++) {
            frameBuffer[i][j] = 0;
        }
    }
    return CLS;
}

int Chip::op00EE(){
    stackPop();
    PC = stackTop();
    return RET;
}

int Chip::op1NNN(){
    PC = MASK_0NNN(opcode);
    return JP_Addr;
}

int Chip::op2NNN(){
    stackPush(PC);
    PC = MASK_0NNN(opcode);
    return CALL_Addr;
}

//may cause errors check if we incremented PC in fetch 
int Chip::op3XNN(){
    PC += (V[MASK_0N00(opcode)] == MASK_0NNN(opcode)) ? 2 : 0;
    return SE_Vx_Byte;
}


int Chip::op4XNN(){
    PC += (V[MASK_0N00(opcode)] != MASK_0NNN(opcode)) ? 2 : 0;
    return SNE_Vx_Byte;
}

int Chip::op5XY0(){
    PC += (V[MASK_0N00(opcode)] == V[MASK_00N0(opcode)]) ? 2 : 0;
    return SE_Vx_Vy;
}

int Chip::op6XNN(){
    V[MASK_0N00(opcode)] = MASK_00NN(opcode);
    return LD_Vx_Byte;
}

int Chip::op7XNN(){
    V[MASK_0N00(opcode)] += MASK_00NN(opcode);
    std::cout << MASK_000N(opcode) << "yes";
    return ADD_Vx_Byte;
}

int Chip::op8XY0(){
    V[MASK_0N00(opcode)] = V[MASK_00N0(opcode)];
    return LD_Vx_Vy;
}

int Chip::op8XY1(){
    V[MASK_0N00(opcode)] |= V[MASK_0N00(opcode)];
    return OR_Vx_Vy;
}

int Chip::op8XY2(){
    V[MASK_0N00(opcode)] &= V[MASK_0N00(opcode)];
    return AND_Vx_Vy;
}

int Chip::op8XY3(){
    V[MASK_0N00(opcode)] ^= V[MASK_0N00(opcode)];
    return XOR_Vx_Vy;
}

int Chip::op8XY4(){
    V[MASK_0N00(opcode)] += V[MASK_00N0(opcode)];
    V[0xF] = (V[MASK_0N00(opcode)] > 0xFF) ? 1 : 0;
    return ADD_Vx_Vy;
}

int Chip::op8XY5(){
    V[MASK_0N00(opcode)] = V[MASK_00N0(opcode)] - V[MASK_0N00(opcode)];
    V[0xF] = (V[MASK_0N00(opcode)] >= V[MASK_00N0(opcode)]) ? 1 : 0;
    return SUB_Vx_Vy;
}

int Chip::op8XY6(){
    V[0xF] = V[MASK_0N00(opcode)] & 1;
    V[MASK_0N00(opcode)] >>= 1;
    return SHR_Vx;
}

int Chip::op8XY7(){
    V[MASK_0N00(opcode)] = V[MASK_0N00(opcode)] - V[MASK_00N0(opcode)];
    V[0xF] = (V[MASK_00N0(opcode)] >= V[MASK_0N00(opcode)]) ? 1 : 0;
    return SUBN_Vx_Vy;
}

int Chip::op8XYE(){
    V[0xF] = V[MASK_0N00(opcode)] >> 7;
    V[MASK_0N00(opcode)] <<= 1;
    return SHL_Vx;
}

int Chip::op9XY0(){
    PC += (V[MASK_0N00(opcode)] != V[MASK_00N0(opcode)]) ? 2 : 0;
    return SNE_Vx_Vy;
}

int Chip::opANNN(){
    I = MASK_0NNN(opcode);
    return LD_I_Addr;
}

int Chip::opBNNN(){
    PC = MASK_0NNN(opcode) + V[0x0];
    return JP_V0_Addr;
}

int Chip::opCXNN(){
    uint8_t r = rand() % UINT8_MAX;
    V[MASK_0N00(opcode)] = r & MASK_00NN(opcode);
    return RND_Vx_Byte;
}

int Chip::opDXYN(){
    uint16_t x = V[MASK_0N00(opcode)]; //start x
    uint16_t y = V[MASK_00N0(opcode)]; //start y
    uint16_t N = MASK_000N(opcode);
    V[0xF] = 0;
    //row are sized up to N 
    std::cout << x << " | " << y << "\n";
    for (int row=0; row<N; row++) {
        //col are sized 8 max
        uint8_t spriteByte = mem[I + row];
        for (int col=0; col<maxSpriteWidth; col++){
            uint8_t pixel = (spriteByte >> ((maxSpriteWidth - 1) - col)) & 0x01;
            V[0xF] = (frameBuffer[x + col][y + row]) ? 1 : 0;
            frameBuffer[(x + col)][(y + row)] ^= pixel;
        }
    }
    return DRW_Vx_Vy_Nibble;
}

int Chip::opEX9E(){
    PC += (input[V[MASK_0N00(opcode)]] == 1) ? 2 : 0;
    return SKP_Vx;
}

int Chip::opEXA1(){
    PC += (input[V[MASK_0N00(opcode)]] != 1) ? 2 : 0;
    return SKNP_Vx;
}

int Chip::opFX07(){
    V[MASK_0N00(opcode)] = DT;
    return LD_Vx_Delay;
}

int Chip::opFX0A(){
    bool pressed = false;
    for (int i=0; i<inputSize; i++) {
        if(input[i] == 0) {
            pressed = true;
            V[MASK_0N00(opcode)] = i;
            break;
        }
    }
    PC -= (!pressed) ? 2 : 0;
    return LD_Vx_Key;
}

int Chip::opFX15(){
    DT = V[MASK_0N00(opcode)];
    return LD_Delay_Vx;
}

int Chip::opFX18(){
    ST = V[MASK_0N00(opcode)];
    return LD_Sound_Vx;
}

int Chip::opFX1E(){
    I += V[MASK_0N00(opcode)];

    return ADD_I_Vx;
}

int Chip::opFX29(){ //its length is 5
    I = startFont + (V[MASK_0N00(opcode)] * 5);
    return LD_F_Vx;
}

int Chip::opFX33(){
    mem[I] = V[MASK_0N00(opcode)] / 100 % 10;
    mem[I + 1] = V[MASK_0N00(opcode)] / 10 % 10;
    mem[I + 2] = V[MASK_0N00(opcode)] % 10;
    return LD_B_Vx;
}

int Chip::opFX55(){
    for(int i=0; i<MASK_0N00(opcode); i++) {
        mem[I + i] = V[i];
    }
    return LD_I_Vx;
}

int Chip::opFX65(){
    for(int i=0; i<MASK_0N00(opcode); i++) {
        V[i] = mem[I + i];
    }
    return LD_Vx_I;
}

//===========================================
//	INTERPRET
//===========================================
uint16_t Chip::fetch() {
    uint16_t instr = BYTES_TO_UINT16(mem[PC], mem[PC + 1]);
    PC += 2;
    opcode = instr;
    return instr;
}

Chip::instruction Chip::decode(uint16_t instr) {
    //right shift 12 to isolate first 4 bits
    uint16_t MSB = instr >> 12; 
    return lookupGeneral[MSB];
}

//for test purposes
Chip::instruction Chip::decode(bool debug, uint16_t instr) {
    return lookupGeneral[instr];
}

int Chip::execute(Chip::instruction funct){
    return ((*this).*(funct))();
}

//===========================================
//	STACK OPERATIONS
//===========================================

int Chip::stackPush(uint16_t item) {
    ++SP;
    if(SP >= stackSize) {
        std::cout << "error<Stack Overflow>\n";
        return -1;
    }
    stack[SP] = item;
    return item;
}

int Chip::stackPop() {
    int pop = stack[SP];
    --SP;
    if(SP < 0) {
        std::cout << "error<Attempt to Pop empty Stack>\n";
        return -2;
    }
    return pop;
}

uint16_t Chip::stackTop() {
    return stack[SP];
}

//===========================================
//	TESTING
//===========================================

void Chip::printRegisters() {
    std::string out;
    for (int i=0; i<16; i++) {
        if(V[i] != 0) {
            std::cout<< "V["<< i << "]:" << (int)V[i] << "| ";
        }
    }
}

void Chip::printFunctionExecuted(int executeCode) {
    switch(executeCode) {
        case NIL:
            std::cout << "<Instruction Does Not Exist>" <<std::endl;
            break;
        case CLS:
            std::cout << "<Clear Screen>" <<std::endl;
            break;         
        case RET:
            std::cout << "<Return from subroutine>" <<std::endl;
            break;          
        case JP_Addr:
            std::cout << "<Jump to address NNN>" <<std::endl;
            break;      
        case CALL_Addr:
            std::cout << "<Call Address NNN>" <<std::endl;
            break;     
        case SE_Vx_Byte:
            std::cout << "<Skips next if Vx == NN>" <<std::endl;
            break;   
        case SNE_Vx_Byte:
            std::cout << "<Skips next if Vx != NN>" <<std::endl;
            break;    
        case SE_Vx_Vy:
            std::cout << "<Skips next if Vx == Vy>" <<std::endl;
            break;     
        case LD_Vx_Byte:
            std::cout << "<Load NN into Vx>" <<std::endl;
            break;   
        case ADD_Vx_Byte:
            std::cout << "<Add NN to Vx>" <<std::endl;
            break;  
        case LD_Vx_Vy:
            std::cout << "<Load Vy into Vx>" <<std::endl;
            break;     
        case OR_Vx_Vy:
            std::cout << "<Set Vx = Vx OR Vy>" <<std::endl;
            break;      
        case AND_Vx_Vy:
            std::cout << "<Set Vx = Vx AND Vy >" <<std::endl;
            break;   
        case XOR_Vx_Vy:
            std::cout << "<Set Vx = Vx XOR Vy>" <<std::endl;
            break;    
        case ADD_Vx_Vy:
            std::cout << "<Set Vx = Vx + Vy, set VF = carry>" <<std::endl;
            break;     
        case SUB_Vx_Vy:
            std::cout << "<Set Vx = Vx - Vy, set VF = NOT borrow>" <<std::endl;
            break;    
        case SHR_Vx:
            std::cout << "<Set Vx = Vx SHR 1>" <<std::endl;
            break;       
        case SUBN_Vx_Vy:
            std::cout << "<Set Vx = Vy - Vx, set VF = NOT borrow>" <<std::endl;
            break;   
        case SHL_Vx:
            std::cout << "<Set Vx = Vx SHL 1>" <<std::endl;
            break;       
        case SNE_Vx_Vy:
            std::cout << "<Skip next instruction if Vx != Vy>" <<std::endl;
            break;    
        case LD_I_Addr:
            std::cout << "<Load address NNN into I>" <<std::endl;
            break;     
        case JP_V0_Addr:
            std::cout << "<Jump to address NNN + V0>" <<std::endl;
            break;   
        case RND_Vx_Byte:
            std::cout << "<Set Vx = random byte AND NN>" <<std::endl;
            break;   
        case DRW_Vx_Vy_Nibble:
            std::cout << "<Draw sprite at (Vx, Vy) with N bytes of sprite data>" <<std::endl;
            break;
        case SKP_Vx:
            std::cout << "<Skip next instruction if key with value Vx is pressed>" <<std::endl;
            break;       
        case SKNP_Vx:
            std::cout << "<Skip next instruction if key with value Vx is not pressed>" <<std::endl;
            break;        
        case LD_Vx_Delay:
            std::cout << "<Load delay timer into Vx>" <<std::endl;
            break;    
        case LD_Vx_Key:
            std::cout << "<Wait for a key press and store it in Vx>" <<std::endl;
            break;     
        case LD_Delay_Vx:
            std::cout << "<Set delay timer to Vx>" <<std::endl;
            break;  
        case LD_Sound_Vx:
            std::cout << "<Set sound timer to Vx>" <<std::endl;
            break;   
        case ADD_I_Vx:
            std::cout << "<Add Vx to I>" <<std::endl;
            break;    
        case LD_F_Vx:
            std::cout << "<Set I to the location of the sprite for digit Vx>" <<std::endl;
            break;        
        case LD_B_Vx:
            std::cout << "<Store BCD representation of Vx in memory locations I, I+1, and I+2>" <<std::endl;
            break;      
        case LD_I_Vx:
            std::cout << "<Store registers V0 to Vx in memory starting at address I>" <<std::endl;
            break;       
        case LD_Vx_I:
            std::cout << "<Read registers V0 to Vx from memory starting at address I>" <<std::endl;
            break;    
        default:
            std::cout << "UNDEFINED" <<std::endl;  
            break;
    }
}

void Chip::printDebug() {
    std::cout << "I : "<< std::hex << I << "\n";
    std::cout << "PC : "<< std::hex << PC << "\n";
    std::cout << "opcode : "<< std::hex << opcode << "\n";
    printRegisters();
    std::cout << "\n";
}

}
