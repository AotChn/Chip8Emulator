#include "gtest/gtest.h"
#include <set>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include "../../src/app/app.h"





//------------------------------------------------------------------------------------------
//Files we are testing:

  //chip_8.h

//------------------------------------------------------------------------------------------

//testing macro that converts two bytes into uint16
TEST(CHIP_MACROS, bytes_to_uint16_t){
  int test = 0;
  uint8_t byte1, byte2;
  uint16_t targetHex;

//1
  byte1 = 0xA0, byte2 = 0xB4, ++test;
  targetHex = 0xA0B4;
  EXPECT_EQ(BYTES_TO_UINT16(byte1, byte2), targetHex) << "failed test: " << test;
//2 
  byte1 = 0xFF, byte2 = 0xBA, ++test;
  targetHex = 0xFFBA;
  EXPECT_EQ(BYTES_TO_UINT16(byte1, byte2), targetHex) << "failed test: " << test;
//3
  byte1 = 0x23, byte2 = 0x54, ++test;
  targetHex = 0x2354;
  EXPECT_EQ(BYTES_TO_UINT16(byte1, byte2), targetHex) << "failed test: " << test;
//4
  byte1 = 0xfc, byte2 = 0xd3, ++test;
  targetHex = 0xfcd3;
  EXPECT_EQ(BYTES_TO_UINT16(byte1, byte2), targetHex) << "failed test: " << test;
//5
  byte1 = 0xff, byte2 = 0xff, ++test;
  targetHex = 0xffff;
  EXPECT_EQ(BYTES_TO_UINT16(byte1, byte2), targetHex) << "failed test: " << test;
//6
  byte1 = 0x0a, byte2 = 0x4b, ++test;
  targetHex = 0x0a4b;
  EXPECT_EQ(BYTES_TO_UINT16(byte1, byte2), targetHex) << "failed test: " << test;
}

TEST(CHIP_INSTRUCTIONS, genFunctions) {
  chip8::Chip chip;
  int targetFunction;
  
  // targetFunction = chip8::INSTR_CODE::LOOKUP_0;
  // EXPECT_EQ(chip.execute(chip.decode(true, 0x0)), targetFunction);

  targetFunction = chip8::INSTR_CODE::JP_Addr;
  EXPECT_EQ(chip.execute(chip.decode(true, 0x1)), targetFunction);

  targetFunction = chip8::INSTR_CODE::CALL_Addr;
  EXPECT_EQ(chip.execute(chip.decode(true, 0x2)), targetFunction);

  targetFunction = chip8::INSTR_CODE::SE_Vx_Byte;
  EXPECT_EQ(chip.execute(chip.decode(true, 0x3)), targetFunction);

  targetFunction = chip8::INSTR_CODE::SNE_Vx_Byte;
  EXPECT_EQ(chip.execute(chip.decode(true, 0x4)), targetFunction);

  targetFunction = chip8::INSTR_CODE::SE_Vx_Vy;
  EXPECT_EQ(chip.execute(chip.decode(true, 0x5)), targetFunction);

  targetFunction = chip8::INSTR_CODE::LD_Vx_Byte;
  EXPECT_EQ(chip.execute(chip.decode(true, 0x6)), targetFunction);

  targetFunction = chip8::INSTR_CODE::ADD_Vx_Byte;
  EXPECT_EQ(chip.execute(chip.decode(true, 0x7)), targetFunction);

  // targetFunction = chip8::INSTR_CODE::LOOKUP_8;
  // EXPECT_EQ(chip.execute(chip.decode(true, 0x8)), targetFunction);

  targetFunction = chip8::INSTR_CODE::SNE_Vx_Vy;
  EXPECT_EQ(chip.execute(chip.decode(true, 0x9)), targetFunction);

   targetFunction = chip8::INSTR_CODE::LD_I_Addr;
  EXPECT_EQ(chip.execute(chip.decode(true, 0xA)), targetFunction);

  targetFunction = chip8::INSTR_CODE::JP_V0_Addr;
  EXPECT_EQ(chip.execute(chip.decode(true, 0xB)), targetFunction);

  targetFunction = chip8::INSTR_CODE::RND_Vx_Byte;
  EXPECT_EQ(chip.execute(chip.decode(true, 0xC)), targetFunction);

  targetFunction = chip8::INSTR_CODE::DRW_Vx_Vy_Nibble;
  EXPECT_EQ(chip.execute(chip.decode(true, 0xD)), targetFunction);

  // targetFunction = chip8::INSTR_CODE::LOOKUP_E;
  // EXPECT_EQ(chip.execute(chip.decode(true, 0xE)), targetFunction);

  // targetFunction = chip8::INSTR_CODE::LOOKUP_F;
  // EXPECT_EQ(chip.execute(chip.decode(true, 0xF)), targetFunction);

}


int main(int argc, char **argv) {
  std::srand(time(nullptr));
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}
