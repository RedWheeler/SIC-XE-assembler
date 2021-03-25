#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <stdexcept>

#ifndef _UTILITIES_H_
#define _UTILITIES_H_

int strtoint(std::string str);
std::vector<bool> dectobin(int decimal, int bit);
std::vector<bool> decto2comp(int decimal, int bits);
int hextodec(std::string hex);
std::string dectohex(int decimal, int digits);
int bintodec(std::vector<bool> binary);
void printbin(std::vector<bool> binary);

#endif
