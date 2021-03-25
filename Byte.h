#include "Instruction.h"

#ifndef _BYTE_H_
#define _BYTE_H_

class Byte : public Instruction
{
  public:
    Byte(int address, std::string operands);
    ~Byte(void);
    int assemble(void);
    int length(void);
    int address(void);
  private:
    int address_;
    char type_;
    std::string operands_;
};
#endif
