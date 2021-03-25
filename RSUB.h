#include "Instruction.h"

#ifndef _RSUB_H_
#define _RSUB_H_

class RSUB : public Instruction
{
  public:
    RSUB(int address);
    ~RSUB(void);
    int assemble(void);
    int length(void);
    int address(void);
  private:
    int address_;
};

#endif
