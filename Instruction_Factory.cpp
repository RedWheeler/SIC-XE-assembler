#include "Instruction_Factory.h"

Instruction_Factory:: Instruction_Factory(std::map<std::string, int>& symtable, int* pc, std::string* base)
 :symtable_(symtable), pc_(pc), base_(base)
{
  // Format 1 Instruction opcodes
  optable_1_["FIX"] = 0xc4;
  optable_1_["FLOAT"] = 0xc0;
  optable_1_["HIO"] = 0xf4;
  optable_1_["NORM"] = 0xc8;
  optable_1_["SIO"] = 0xf0;
  optable_1_["TIO"] = 0xf8;

  // Format 2 Instruction opcodes
  optable_2_["ADDR"] = 0x90;
  optable_2_["CLEAR"] = 0xb4;
  optable_2_["COMPR"] = 0xa0;
  optable_2_["DIVR"] = 0x9c;
  optable_2_["MULR"] = 0x98;
  optable_2_["RMO"] = 0xac;
  optable_2_["SHIFTL"] = 0xa4;
  optable_2_["SHIFTR"] = 0xa8;
  optable_2_["SUBR"] = 0x94;
  optable_2_["SVC"] = 0x80;
  optable_2_["TIXR"] = 0xb8;

  // Format 3/4 Instruction opcodes
  optable_3_["ADD"] =  0x18;
  optable_3_["ADDF"] = 0x58;
  optable_3_["AND"] = 0x40;
  optable_3_["COMP"] = 0x28;
  optable_3_["COMPF"] = 0x88;
  optable_3_["DIV"] = 0x24;
  optable_3_["DIVF"] = 0x64;
  optable_3_["J"] = 0x3c;
  optable_3_["JEQ"] = 0x30;
  optable_3_["JGT"] = 0x34;
  optable_3_["JLT"] = 0x38;
  optable_3_["JSUB"] = 0x48;
  optable_3_["LDA"] = 0x00;
  optable_3_["LDB"] = 0x68;
  optable_3_["LDCH"] = 0x50;
  optable_3_["LDF"] = 0x70;
  optable_3_["LDL"] = 0x08;
  optable_3_["LDS"] = 0x6c;
  optable_3_["LDT"] = 0x74;
  optable_3_["LDX"] = 0x04;
  optable_3_["LPS"] = 0xd0;
  optable_3_["MUL"] = 0x20;
  optable_3_["MULF"] = 0x60;
  optable_3_["OR"] = 0x44;
  optable_3_["RD"] = 0xd8;
  //optable_3_["RSUB"] = 0x4c;
  optable_3_["SSK"] = 0xec;
  optable_3_["STA"] = 0x0c;
  optable_3_["STB"] = 0x78;
  optable_3_["STCH"] = 0x54;
  optable_3_["STF"] = 0x80;
  optable_3_["STI"] = 0xd4;
  optable_3_["STL"] = 0x14;
  optable_3_["STS"] = 0x7c;
  optable_3_["STSW"] = 0xe8;
  optable_3_["STT"] = 0x84;
  optable_3_["STX"] = 0x10;
  optable_3_["SUB"] = 0x1c;
  optable_3_["SUBF"] = 0x5c;
  optable_3_["TD"] = 0xe0;
  optable_3_["TIX"] = 0x2c;
  optable_3_["WD"] = 0xdc;
}

Instruction* Instruction_Factory:: create_instruction(std::string instruction, std::string operands)
{
  
  if(instruction == "BYTE")
    return new Byte(*pc_, operands);
  else if(instruction == "WORD")
    return new Word(*pc_, operands, symtable_);
  else if(instruction == "RSUB")
    return new RSUB(*pc_);
  // Search for Format1 Instruction
  std::map<std::string,	int>::iterator it;
  it = optable_1_.find(instruction);
  if(it != optable_1_.end())
  {
    return new Format1_Instruction(*pc_, it->second);
  }

  // Search for Format2 Instruction
  std::map<std::string, int>::iterator it2;
  it2 = optable_2_.find(instruction);
  if(it2 != optable_2_.end())
  {
    return new Format2_Instruction(*pc_, it2->second, operands);
  }
 
  bool extended = false;
  if(instruction[0] == '+')
  {
    extended = true;
    instruction = instruction.substr(1);
  }
  // Search for Format3/4 Instruction
  std::map<std::string, int>::iterator it3;
  it3 = optable_3_.find(instruction);
  if(it3 != optable_3_.end())
  {
    if(extended)
      return new Format4_Instruction(*pc_, it3->second, operands, symtable_);
    else
      return new Format3_Instruction(*pc_, it3->second, operands, symtable_, *base_);
  }
  // THROW EXCEPTION IF INSTRUCTION NOT FOUND
}
