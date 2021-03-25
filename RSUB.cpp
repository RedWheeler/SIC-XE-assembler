#include "RSUB.h"
#include <iostream>

RSUB:: RSUB(int address)
  :address_(address)
{

}

RSUB:: ~RSUB(void)
{

}

int RSUB:: assemble(void)
{
  return hextodec("4F0000");
}

int RSUB:: length(void)
{
  return 3;
}

int RSUB:: address(void)
{
  return address_;
}
