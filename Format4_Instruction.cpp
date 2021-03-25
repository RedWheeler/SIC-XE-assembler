#include "Format4_Instruction.h"

Format4_Instruction:: Format4_Instruction(int address, int opcode, std::string operands, std::map<std::string, int> & symtable)
  :address_(address), opcode_(opcode), operands_(operands), symtable_(symtable)
{

}

Format4_Instruction:: ~Format4_Instruction(void)
{

}

int Format4_Instruction:: assemble(void)
{
  int TA;
  bool n, i, x, b, p, e;
  b = 0;
  p = 0;
  e = 1;
 
  std::vector<bool> disp;
  std::string ops = operands_;

  // Add opcode - 2 bits to assembled output
  std::vector<bool> assembled = dectobin(opcode_, 8);
  assembled.erase(assembled.begin() + assembled.size() - 1);
  assembled.erase(assembled.begin() + assembled.size() - 1);
  
  // Immediate addressing
  if(ops[0] == '#')
  {
    n = 0;
    i = 1;
    ops.erase(0, 1);
  }
  // Indirect addressing
  else if(ops[0] == '@')
  {
    n = 1;
    i = 0;
    ops.erase(0, 1);
  }
  else
  {
    n = 1;
    i = 1;
  }
  // Indexed addressing
  if(ops[ops.length()-2] == ',' && ops[ops.length()-1] == 'X')
  {
    x = 1;
    ops.erase(ops.length()-1);
    ops.erase(ops.length()-1);
  }
  else
  {
    x = 0;
  }
 if(isdigit(ops[0]))
  {
    TA = strtoint(ops);
    disp = dectobin(TA, 20);
  }
  // Relative addressing
  else
  {
      TA = symtable_[ops];
      disp = dectobin(TA, 20);
  }

  assembled.push_back(n);
  assembled.push_back(i);
  assembled.push_back(x);
  assembled.push_back(b);
  assembled.push_back(p);
  assembled.push_back(e);

  for(int i = 0; i < disp.size(); i++)
  {
    assembled.push_back(disp[i]);
  }
  return bintodec(assembled);
}

int Format4_Instruction:: length(void)
{
  return 4;
}

int Format4_Instruction:: address(void)
{
  return address_;
}
