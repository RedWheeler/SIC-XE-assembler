#include "Instruction.h"

#ifndef _FORMAT1_INSTRUCTION_H_
#define _FORMAT1_INSTRUCTION_H_

class Format1_Instruction : public Instruction
{
  public:
    Format1_Instruction(int addresss, int opcode); 
    ~Format1_Instruction(void);
    int assemble(void);
    int length(void);
    int address(void);

  private:
    int address_;
    int opcode_;
};

#endif
