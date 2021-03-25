#include "Word.h"
#include <sstream>
#include <iostream>
#include "utilities.h"

Word:: Word(int address, std::string operands, std::map<std::string, int> & sym_table)
  :address_(address), 
  operands_(operands),
  sym_table_(sym_table)
{

}

Word:: ~Word(void)
{

}

int Word:: assemble(void)
{
  int value;
  std::string token;
  std::stringstream ss(operands_);
  getline(ss, token, '-');
  if(token == "*")
    value = address_;
  else
    value = sym_table_[token];
  while(getline(ss, token, '-'))
  {
    if(token == "*")
      value -= address_;
    else
      value -= sym_table_[token];
  }
  return value;
}

int Word:: length(void)
{
  return 3;
}

int Word:: address(void)
{
  return address_;
}
