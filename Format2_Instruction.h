#include "Instruction.h"
#include <map>

#ifndef _FORMAT2_INSTRUCTION_H_
#define _FORMAT2_INSTRUCTION_H_

class Format2_Instruction : public Instruction
{
  public: 
    Format2_Instruction(int address, int opcode, std::string operands);
    ~Format2_Instruction(void);
    int assemble(void);
    int length(void);
    int address(void);

  private:
    int address_;
    int opcode_;
    std::string operands_;
    std::map<char, int> regtable_;
};

#endif
