#include "Format3_Instruction.h"
#include <iostream>

Format3_Instruction:: Format3_Instruction(
    int address, int opcode, std::string operands, std::map<std::string, int> & symtable, std::string base)
  :address_(address), opcode_(opcode), operands_(operands), symtable_(symtable), base_(base)
{

}

Format3_Instruction:: ~Format3_Instruction(void)
{

}

int Format3_Instruction:: assemble(void)
{

  int TA;
  int PC = address_ + length();
  bool n, i, x, p, b, e;

  e = 0;
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
    disp = dectobin(TA, 12);
    b = 0;
    p = 0;
  }
  // Relative addressing
  else
  {
    try
    {
      TA = symtable_[ops];
      int displacement = TA - PC;
      disp = decto2comp(displacement, 12);
      b = 0;
      p = 1;
    }
    catch(...)
    {
      try
      {
	TA = symtable_[ops];
	int displacement = TA - symtable_[base_];
	disp = dectobin(displacement, 12);
	b = 1;
	p = 0;
      }
      catch(...)
      {
	// SHOULD THROW EXCEPTION HERE
	return 0;
      }
    }
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

int Format3_Instruction:: length(void)
{
  return 3;
}

int Format3_Instruction:: address(void)
{
  return address_;
}
