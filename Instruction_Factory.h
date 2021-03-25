#ifndef _INSTRUCTION_FACTORY_H_
#define _INSTRUCTION_FACTORY_H_

#include <string>
#include <map>
#include "Byte.h"
#include "Word.h"
#include "RSUB.h"
#include "Format1_Instruction.h"
#include "Format2_Instruction.h"
#include "Format3_Instruction.h"
#include "Format4_Instruction.h"

class Instruction_Factory
{
  public:
    Instruction_Factory(std::map<std::string, int>& symtable, int* pc, std::string* base);
    Instruction* create_instruction(std::string instruction, std::string operands);
  private:
    std::map<std::string, int> optable_1_;
    std::map<std::string, int> optable_2_;
    std::map<std::string, int> optable_3_;
    std::map<std::string, int> optable_4_;
    std::map<std::string, int>& symtable_;
    int* pc_;
    std::string* base_;
};

#endif
