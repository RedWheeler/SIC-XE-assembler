#include "Instruction.h"
#include <map>

#ifndef _WORD_H_
#define _WORD_H_

class Word : public Instruction
{
  public:
    Word(int address, std::string operands, std::map<std::string, int> & sym_table);
    ~Word(void);
    int assemble(void);
    int length(void);
    int address(void);
  private:
    int address_;
    std::map<std::string, int> & sym_table_;
    std::string operands_;
};
#endif
