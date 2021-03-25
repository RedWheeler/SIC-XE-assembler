#include "Byte.h"

Byte:: Byte(int address, std::string operands)
  :address_(address)
{
  // Input Device
  if (operands[0] == 'X' && operands.size() == 5)
  {
    type_ = 'X';
    operands_ = operands.substr(2, 2);
  }
  // String
  else if (operands[0] == 'C' && operands[1] == '\'' && operands[operands.size()-1] == '\'')
  {
    type_ = 'C';
    operands_ = operands.substr(2, operands.size()-3);
  }
  // THROW EXCEPTION HERE
  else
  {

  }
}

Byte:: ~Byte(void)
{

}

int Byte:: assemble(void)
{
  if (type_ == 'X')
    return hextodec(operands_);
  else if (type_ == 'C')
  {
    std::vector<bool> binary;
    std::vector<bool> ascii_char;
    int length = operands_.length();
    for(int i = 0; i < length; i++)
    {
      ascii_char = dectobin((int)operands_[i], 8);
      for (int j = 0; j < 8; j++)
	binary.push_back(ascii_char[j]);
    }
    // Return ASCII hex
    return bintodec(binary);
  }
}

int Byte:: length(void)
{
  if (type_ == 'X')
    return 1;
  if (type_ == 'C')
    return operands_.size();
}

int Byte:: address(void)
{
  return address_;
}
