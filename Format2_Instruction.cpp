#include "Format2_Instruction.h"

Format2_Instruction:: Format2_Instruction(int address, int opcode, std::string operands)
  :address_(address), opcode_(opcode), operands_(operands)
{
  regtable_['A'] = 0;
  regtable_['X'] = 1;
  regtable_['L'] = 2;
  regtable_['B'] = 3;
  regtable_['S'] = 4;
  regtable_['T'] = 5;
  regtable_['F'] = 6;
}

Format2_Instruction:: ~Format2_Instruction(void)
{

}

int Format2_Instruction:: assemble(void)
{  
  std::vector<bool> assembled = dectobin(opcode_, 8);
  std::vector<bool> r1 = dectobin(regtable_[operands_[0]], 4);

  for (int i = 0; i < r1.size(); i++)
    assembled.push_back(r1[i]);

  std::vector<bool> r2;
  // Two register instructions 
  if (operands_.length() == 3)
    r2 = dectobin(regtable_[operands_[2]], 4);
  // One register instructions
  else
    r2 = dectobin(0, 4);
  for (int i = 0; i < r2.size(); i++)
    assembled.push_back(r2[i]);

  return bintodec(assembled);
}

int Format2_Instruction:: length(void)
{
  return 2;
}

int Format2_Instruction:: address(void)
{
  return address_;
}
