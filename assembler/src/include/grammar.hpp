#pragma once

#include <map>
#include <string>
#include <vector>

#include "token.hpp"
#include "instruction.hpp"

struct Grammar {
    // Remove all useless tokens as spaces, tabs, newlines, etc
    std::vector<Token> clear(const std::vector<Token>& tokens);
    
    // Process pre compilation instructions, checks for unexpected tokens according 
    // to syntax rules and generate the program instruction list.
    bool compile(bool pre_compilation, Program& program);

    void add_entry(Instruction entry);
private:
    // The instruction entries. Is used to check the syntax.
    std::vector<Instruction> entries;
};
