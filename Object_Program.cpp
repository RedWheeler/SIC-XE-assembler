#include "Object_Program.h"
#include "utilities.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>

Object_Program:: Object_Program(std::string program_name, int starting_address, std::map<std::string, int>& sym_table)
  :program_name_(program_name), 
  starting_address_(starting_address_),
  sym_table_(sym_table)
{
  text_records_.push_back(std::vector<Instruction*>());
  external_references_ = new std::map<std::string, std::vector<int> > ();
}

Object_Program:: ~Object_Program(void)
{
  delete external_references_;
}

void Object_Program:: write_to_file(int ending_address)
{
  std::ofstream output_file;
  output_file.open(program_name_.c_str());
  // Print header record
  std::string starting_address = dectohex(starting_address_, 6);
  std::string program_length = dectohex(ending_address - starting_address_, 6);
  std::string padded_name = program_name_.insert(program_name_.size(), 6-program_name_.size(), ' ');
  std::string header_record = "H" +  padded_name + starting_address + program_length;

  output_file << header_record << std::endl;

  // Print define record
  std::string define_record = "D";
  for (int i = 0; i < define_entries_.size(); i++)
  {
    std::string current_entry = define_entries_[i];
    define_record += current_entry.insert(current_entry.size(), 6-current_entry.size(), ' ');
    define_record += dectohex(sym_table_[current_entry], 6);
  }
  if(define_record.size() != 1)
    output_file << define_record << std::endl;

  // Print refer record
  std::string refer_record = "R";
  for (int i = 0; i < refer_entries_.size(); i++)
  {
    std::string current_entry = refer_entries_[i];
    refer_record += current_entry.insert(current_entry.size(), 6-current_entry.size(), ' ');
  }
  if(refer_record.size() != 1)
    output_file << refer_record << std::endl;

  // Print text records
  for (int i = 0; i < text_records_.size(); i++)
  {
    std::vector<Instruction*> current_record = text_records_[i];
    std::string record_length = dectohex(text_record_length(current_record), 2);
    std::string record_start = dectohex(current_record[0]->address(), 6);
    std::string text_record = "T" + record_start + record_length;
    for (int j = 0; j < current_record.size(); j++)
    {
      text_record += dectohex(current_record[j]->assemble(), current_record[j]->length()*2);
    }
    output_file << text_record << std::endl;
  }

  for (int i = 0; i < refer_entries_.size(); i++)
  {
    std::string symbol = refer_entries_[i];
    std::vector<int> references = external_references_->operator[](symbol);
    for(int j = 0; j < references.size(); j++)
    {
      std::string sign = "+";
      int reference = references[j];
      if(reference < 0)
      {
	sign = "-";
	reference = -reference;
      }
      std::string modification_record = "M" + dectohex(reference+1, 6) + dectohex(5, 2) + sign + symbol;
      output_file << modification_record << std::endl; 
    }
  }
  std::string end_record = "E" + dectohex(text_records_[0][0]->address(), 6);
  output_file << end_record << std::endl;
}


void Object_Program:: new_text_entry(Instruction* entry)
{
  std::vector<Instruction*> current_record = text_records_.back();

  if(!current_record.empty())
  {
    Instruction* last_entry = current_record.back();
    int next_address = last_entry->address() + last_entry->length();  
    if(text_record_length(current_record)*2 + entry->length()*2 > 60 || entry->address() != next_address)
    {
      std::vector<Instruction*> new_record (1, entry);
      text_records_.push_back(new_record);
      return;
    }
  }
  text_records_.back().push_back(entry);
}

void Object_Program:: new_define_entry(std::string symbol)
{
  define_entries_.push_back(symbol);
}

void Object_Program:: new_refer_entry(std::string symbol)
{
  refer_entries_.push_back(symbol);
  external_references_->operator[](symbol) = std::vector<int> ();
}

void Object_Program:: new_text_record(void)
{
  if(text_records_.back().size() != 0)
    text_records_.push_back(std::vector<Instruction*>());
}

void Object_Program:: new_external_reference(std::string symbol, int address)
{
  //FIRST CHECK IF IN REFER RECORDS
  external_references_->operator[](symbol).push_back(address);
}

int Object_Program:: text_record_length(std::vector<Instruction*> text_record)
{
  int record_length = 0;
  int instruction_count = text_record.size();

  for (int i = 0; i < instruction_count; i++)
    record_length += text_record[i]->length();

  return record_length;
}


