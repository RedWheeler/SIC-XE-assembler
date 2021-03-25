#include <iostream>
#include "utilities.h"

int strtoint(std::string str)
{
  int i;
  std::istringstream(str) >> i;
  return i;
}

// Return a vector<bool> representation of a binary string
std::vector<bool> dectobin(int decimal, int bits)
{
  std::vector<bool> binary(bits, false);
  int place; 
  for(int i = bits-1; i >= 0; i--)
  {
    place = pow(2, i);
    if(decimal >= place)
    {
      decimal -= place;
      binary[bits-i-1] = 1;
    }
  }
  if(decimal != 0)
    throw std::length_error("Unable to represent value in specified number of bits");
  
  return binary;
}

// Get 2's complement representation of decimal value 
std::vector<bool> decto2comp(int decimal, int bits)
{
  if(decimal < -1*pow(2, bits) || decimal > pow(2, bits)-1)
    throw std::length_error("Unable to represent value in specified number of bits");
  
  std::vector<bool> binary = dectobin(std::abs(decimal), bits);
  if(decimal >= 0)
    return binary;
  else
  {
    // Flip all bits
    for(int i = 0; i < bits; i++)
    {
      if(binary[i])
	binary[i] = false;
      else
	binary[i] = true;
    }
    // Add 1
    bool carry = true;
    int index = bits-1;
    while(carry)
    {
      if (binary[index] && carry)
	binary[index] = false;
      else
      {
	binary[index] = true;
	carry = false;
      }
      index--;
    }

    bool found_zero = false;
    // Set preceding 1's
    index = 0;
    while(!binary[index])
    {
      binary[index] = true;
      index++;
    }
    return binary;
  }
}

int hextodec(std::string hex)
{
  int decimal;
  std::stringstream ss;
  ss << std::hex << hex;
  ss >> decimal;
  return decimal;
}

std::string dectohex(int decimal, int digits)
{
  std::stringstream ss;
  ss << std::uppercase << std::hex << decimal;
  std::string unpadded = ss.str();
  // Pad hex with specified number of preceding 0's
  return unpadded.insert(0, digits - unpadded.size(), '0');
}
int bintodec(std::vector<bool> binary)
{
  int decimal = 0;
  int bits = binary.size();

  for(int i = 0; i < bits; i++)
  {
    if(binary[i] == 1)
    {
      decimal += pow(2, bits - i - 1);
    }
  }
  return decimal;
}

void printbin(std::vector<bool> binary)
{
  for(int i = 0; i < binary.size(); i++)
  {
    std::cout << binary[i];
  }
}
