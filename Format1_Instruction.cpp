#include "Format1_Instruction.h"
#include <iostream>

Format1_Instruction:: Format1_Instruction(int address, int opcode)
  :address_(address), opcode_(opcode)
{

}

Format1_Instruction:: ~Format1_Instruction(void)
{

}

int Format1_Instruction:: assemble(void)
{
  return opcode_;
}

int Format1_Instruction:: length(void)
{
  return 1;
}

int Format1_Instruction:: address(void)
{
  return address_;
}
