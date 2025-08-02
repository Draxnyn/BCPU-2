#pragma once

#include "syntax.hpp"
#include "token.hpp"

#include <map>
#include <string>
#include <functional>
#include <vector>

struct Instruction;

struct Program {
    std::map<std::string, int> jump_table;
    // This is the generated instruction list. It's used along with
    // the tokens list to generate the program code.
    std::vector<Instruction> instructions;

    // These will be used in the process of compiling the instructions
    std::vector<Token> tokens;
    size_t token_ptr;

    const Token& get_curr_token();
    // Actual program string, what will be outputed to the file
    std::vector<std::string> program;
    // This is kinda like a program counter, it is used for creating jump tables.
    int program_ptr;
    
    bool error;
    std::string error_str;
    void add_error(std::string str);
    
    // These will be used by the instruction function for fetching the tokens
    void tok_instr();
    std::string tok_keyword();
    int tok_number();
};

// This function is what the instruction being read will call to read and process the following tokens. It may alter program struct, for example, adding entries to jump_table
using p_ftype = std::function<void(Program&)>;
struct Instruction {
    Instruction(Syntax synt, p_ftype const& p_func, bool pre_comp, int size)
    : syntax(synt), process_f(p_func), pre_compile(pre_comp), instr_size(size){
    }
    
    Syntax syntax;
    const p_ftype process_f;
    bool pre_compile;
    int instr_size; // The size in bytes it takes in memory
};
