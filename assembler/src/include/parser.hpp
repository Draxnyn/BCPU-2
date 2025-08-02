#pragma once

#include <string>
#include <vector>
#include <map>

#include "token.hpp"
#include "grammar.hpp"
#include "instruction.hpp"

struct Parser {
    Parser(const std::vector<Token>& tokenss);
    ~Parser();
    
    bool compile();
    bool compile(std::string file_path);

    std::string get_error();
private:
    std::string error;
    std::vector<Token> tokens;
    std::string program_result;

    std::vector<Instruction> instr_set;

    Grammar grammar;
    Program program;

    bool pre_compile();
};
