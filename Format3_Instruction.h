#include "Instruction.h"
#include <map>

#ifndef _FORMAT3_INSTRUCTION_H_
#define _FORMAT3_INSTRUCTION_H_

class Format3_Instruction : public Instruction
{
  public:
    Format3_Instruction(int address, int opcode, std::string operands, std::map<std::string, int> & symtable, std::string base);
    ~Format3_Instruction(void);
    int assemble(void);
    int length(void);
    int address(void);
  private:
    int address_;
    int opcode_;
    std::string operands_;
    std::map<std::string, int> & symtable_;
    std::string base_;
};

#endif
