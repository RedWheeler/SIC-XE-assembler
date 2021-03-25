#include <vector>
#include <fstream>
#include "Instruction.h"
#include <map>

#ifndef _OBJECT_PROGRAM_H_
#define _OBJECT_PROGRAM_H_

class Object_Program
{
  public:
    Object_Program(std::string program_name, int starting_address, std::map<std::string, int>& sym_table);
    ~Object_Program(void);
    void write_to_file(int ending_address);
    void new_text_entry(Instruction* entry);
    void new_define_entry(std::string symbol);
    void new_refer_entry(std::string symbol);
    void new_external_reference(std::string symbol, int address);
    void new_text_record(void);
    std::string program_name_;
    int starting_address_;

  private:
    int text_record_length(std::vector<Instruction*> text_record);
    std::map<std::string, int>& sym_table_;
    std::vector<std::vector<Instruction*> > text_records_;
    std::vector<std::string> refer_entries_;
    std::vector<std::string> define_entries_;
    std::map<std::string, std::vector<int> >* external_references_;

};

#endif
