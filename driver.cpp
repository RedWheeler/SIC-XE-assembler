#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "Instruction_Factory.h"
#include "Object_Program.h"
#include "utilities.h"

bool is_in(std::vector<std::string> vect, std::string value)
{
  bool found = false;
  for (int i = 0; i < vect.size(); i++)
    if (vect[i] == value)
      found = true;
  return found;
}

// given a string of operands, parse it and try to add its tokens to the object program's external reference list 
void check_external_references(std::vector<std::string> vect, std::string value, int address, Object_Program* object_program)
{
  std::string token = "";
  char sign = '+';
  for(int i = 0; i < value.size(); i++)
  {
    char current_char = value[i];
    if(isalnum(current_char) || current_char == '*')
      token.push_back(current_char);
    else
    {
      if(is_in(vect, token))
      {
	if(sign == '-')
	  address = -address;
	object_program->new_external_reference(token, address);
      }
      if(current_char == '-' || current_char == '+')
	sign = current_char;
      token = "";
    }
  }
  if(is_in(vect, token))
  {
    if(sign == '-')
      address = -address;
    object_program->new_external_reference(token, address);
  }
}

int main(int argc, char *argv[])
{
  // Get file name from passed in arguments
  char* file_name = argv[1];
  std::ifstream file;
  file.open(file_name);

  if(file.is_open())
  {    
    // Assembler variables
    std::map<std::string, int> sym_table;
    std::map<std::string, int> block_table;
    std::vector<std::string> block_list;
    std::vector<std::string> external_symbols;
    std::map<std::string, std::string> sym_block_table;
    std::map<std::string, std::string> lit_table;

    // Add default block
    block_list.push_back("");
    std::string current_block = "";
    block_table[current_block] = 0;
    int loc_ctr = block_table[current_block];

    std::string base;
    Object_Program * object_program = new Object_Program("NONAME", 0, sym_table);

    // Utilities
    Instruction_Factory instruction_factory(sym_table, &loc_ctr, &base);
    std::vector<Instruction*> instructions;

    // Input file parsing variables
    std::string line; 
    std::string token;
    std::vector<std::string> tokens;

    // Read lines of input file
    // Pass 1 - populate sym_table and create instructions for every instruction
    //std::string label, command, operands;
    while(getline(file, line, '\r'))
    {
      std::stringstream ss(line);
      // if comment Line,  ignore
      if(line[0] != '.' && line.size() != 0)
      {
	int index = 0;
	while(getline(ss, token, '\t'))
	{
	  if (token[0] != '.')
	  {
	    tokens.push_back(token);
	  }
	  else
	    break;
	}
	std::string label = tokens[0];
	std::string command = tokens[1];
	std::string operands = "";
	if(tokens.size() == 3)
	  operands = tokens[2];
	tokens.clear();

	// Process labels
	if(label != "")
	{
	  if(sym_table.count(label) > 0 && command != "CSECT")
	    std::cout << "Repeat label: " << label << std::endl;
	  // SHOULD THROW AN EXCEPTION HERE
	  sym_table[label] = loc_ctr;
	  sym_block_table[label] = current_block; 
	} 

	// Process operands
	if (operands[0] == '=')
	{
	  std::string lit = operands.substr(1);
	  lit_table[operands] = lit;
	}
	else
	  check_external_references(external_symbols, operands, loc_ctr, object_program);

	// Process commands
	if (command == "START")
	{
	  object_program->starting_address_ = strtoint(operands);
	  if(label != "")
	    object_program->program_name_ = label;
	}
	else if (command == "BASE")
	  base = operands;
	else if (command == "RESW")
	  loc_ctr += 3 * strtoint(operands);
	else if (command == "RESB")
	  loc_ctr += strtoint(operands);
	else if (command == "LTORG" || command == "END")
	{
	  std::map<std::string, std::string>::iterator it;
	  for (it = lit_table.begin(); it != lit_table.end(); it++)
	  {
	    sym_table[it->first] = loc_ctr;
	    sym_block_table[it->first] = current_block;
	    Instruction* instruction = instruction_factory.create_instruction("BYTE", it->second);
	    object_program->new_text_entry(instruction);
	    instructions.push_back(instruction);
	    loc_ctr += instruction->length();
	    lit_table.erase(it);
	  }
	  if (command == "END")
	  {
	    block_table[current_block] = loc_ctr;
	    break;
	  }
	}
	else if (command == "EQU")
	{
	  int value;
	  bool is_relative = false;
	  std::stringstream ss(operands);
	  getline(ss, token, '-');
	  if(token == "*")
	  {
	    value = loc_ctr;
	    is_relative = true;
	  }
	  else
	    value = sym_table[token];
	  while(getline(ss, token, '-'))
	  {
	    if(token == "*")
	    {
	      value -= loc_ctr;
	      is_relative = true;
	    }
	    else
	      value -= sym_table[token];
	  }
	  sym_table[label] = value;
	  if(is_relative)
	    sym_block_table[label] = current_block;
	}
	else if (command == "USE")
	{
	  block_table[current_block] = loc_ctr;	
	  current_block = operands;
	  std::map<std::string, int>::iterator it;
	  it = block_table.find(current_block);
	  if (it == block_table.end())
	  { 
	    block_list.push_back(current_block);
	    block_table[current_block] = 0;
	  }
	  loc_ctr = block_table[current_block];
	  object_program->new_text_record();
	}
	else if (command == "EXTDEF")
	{
	  std::stringstream ss(operands);
	  while(getline(ss, token, ','))
	    object_program->new_define_entry(token);
	}
	else if (command == "EXTREF")
	{
	  std::string symbol;
	  std::stringstream ss(operands);
	  while(getline(ss, symbol, ','))
	  {
	    object_program->new_refer_entry(symbol);
	    sym_table[symbol] = 0;	  
	    external_symbols.push_back(symbol);
	  }
	}
	else if (command == "CSECT")
	{
	  object_program->write_to_file(loc_ctr);
	  sym_table.clear();
	  block_table.clear();
	  block_list.clear();
	  sym_block_table.clear();
	  lit_table.clear();	
	  external_symbols.clear();
	  block_list.push_back("");
	  std::string current_block = "";
	  block_table[current_block] = 0;
	  loc_ctr = block_table[current_block];
	  delete object_program;
	  Object_Program * object_program = new Object_Program(label, 0, sym_table);
	}
	else
	{
	  Instruction* instruction = instruction_factory.create_instruction(command, operands);
	  object_program->new_text_entry(instruction);
	  instructions.push_back(instruction);
	  loc_ctr += instruction->length();
	}
      }
    }
    // Pass 2
    // Resolve block offsets
    int block_start = 0;
    for (int i = 0; i < block_list.size(); i++)
    {
      std::string block_name = block_list[i];
      std::map<std::string, std::string>::iterator it;
      for (it = sym_block_table.begin(); it != sym_block_table.end(); it++)
      {
	std::string label = it->first;
	std::string block = it->second;
	if(block == block_name)
	  sym_table[label] = sym_table[label] + block_start;
      }
      block_start += block_table[block_name];
    }    
    object_program->write_to_file(block_start);
    for(int i = 0; i < instructions.size(); i++)
      std::cout << dectohex(instructions[i]->address(), 4) << " " <<  dectohex(instructions[i]->assemble(), instructions[i]->length()*2) << std::endl;
  }

  else
    std::cout << "Unable to read file" << std::cout;

  return 0;
}
