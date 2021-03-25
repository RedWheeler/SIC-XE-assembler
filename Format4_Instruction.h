#include "Instruction.h"
#include <map>

#ifndef _FORMAT4_INSTRUCTION_H_
#define _FORMAT4_INSTRUCTION_H_

class Format4_Instruction : public Instruction
{
  public:
    Format4_Instruction(int address, int opcode, std::string operands, std::map<std::string, int> & symtable);
    ~Format4_Instruction(void);
    int assemble(void);
    int length(void);
    int address(void);
  private:
    int address_;
    int opcode_;
    std::string operands_;
    std::map<std::string, int> & symtable_;
};

#endif
