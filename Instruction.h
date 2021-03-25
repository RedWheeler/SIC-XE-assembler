#include <string>
#include <vector>
#include "utilities.h"

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

class Instruction
{
  public: 
    virtual int assemble(void) = 0;
    virtual int length(void) = 0;
    virtual int address(void) = 0;
};

#endif
