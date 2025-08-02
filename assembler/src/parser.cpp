#include <iostream>
#include <fstream>
#include <format>

#include "parser.hpp"

Parser::Parser(const std::vector<Token>& tokenss) {
    this->tokens = tokenss;
    {
        auto f = [](Program&p){
            std::string ret;
            p.tok_instr();
            auto reg = p.tok_keyword();
            if (reg == "RA") {
                ret = "1";
            } else if (reg == "RB") {
                ret = "2";
            } else {
                p.add_error("Expected register. Got "+reg);
            }
            p.tok_instr();
            int N = p.tok_number();
            ret += std::format("{:x}", N);
            p.program.push_back(ret);
        };
            this->instr_set.push_back(Instruction(Syntax(4,{T_set, T_Keyword, T_Comma, T_Number}), f, false, 2));
    }
    {
        auto f = [](Program& p) {
            std::string ret;
            p.tok_instr();
            auto rg_1 = p.tok_keyword();
            p.tok_instr();
            auto rg_2 = p.tok_keyword();
            if (rg_1 == "RA" && rg_2 == "RB") {
                ret = "3";
            } else if (rg_1 == "RB" && rg_2 == "RA") {
                ret = "4";
            } else {
                p.add_error("Invalid register operation: " + rg_1 + "->" + rg_2);
            }
            p.program.push_back(ret);
        };
        this->instr_set.push_back(
                Instruction(Syntax(4,{T_mov, T_Keyword, T_Comma, T_Keyword}), f, false, 2));
    }
    {
        auto f = [](Program& p) {
            std::string ret;
            p.tok_instr(); // mov
            p.tok_instr(); // RAM
            p.tok_instr(); // [
            int addr = p.tok_number();
            p.tok_instr(); // ]
            p.tok_instr(); // ,
            std::string reg = p.tok_keyword();
            if (reg == "RA") {
                ret = "6" + std::format("{:x}", addr);
            } else if (reg == "RB"){
                ret = "8" + std::format("{:x}", addr);
            } else {
                p.add_error("Invalid register: " + reg);
            }
            p.program.push_back(ret);
        };
        this->instr_set.push_back(
                Instruction(Syntax(7,{T_mov, T_Ram, T_OpenBrackets, T_Number, T_CloseBrackets, T_Comma, T_Keyword}), f, false, 2));
    }
    {
        auto f = [](Program& p) {
            std::string entry = p.tok_keyword(); // Section keyword
            p.tok_instr();
            if (!p.jump_table.contains(entry))
                p.jump_table[entry] = p.program_ptr;
        };
        this->instr_set.push_back(
                Instruction(Syntax(2,{T_Keyword,T_TwoDots}), f, true, 0));
    }
    {
        auto f = [](Program& p) {
            p.tok_instr(); // add
            p.tok_instr(); // RAM
            p.tok_instr(); // [
            int N = p.tok_number();
            p.tok_instr(); // ]
            std::string ret = "9";
            ret += std::format("{:x}", N);
            p.program.push_back(ret);
        };
        this->instr_set.push_back(
                Instruction(Syntax(5,{T_add,T_Ram,T_OpenBrackets,T_Number,T_CloseBrackets}), f, false, 2));
    }
    {
        auto f = [](Program& p) {
            p.tok_instr(); // sub
            p.tok_instr(); // RAM
            p.tok_instr(); // [
            int N = p.tok_number();
            p.tok_instr(); // ]
            std::string ret = "A";
            ret += std::format("{:x}", N);
            p.program.push_back(ret);
        };
        this->instr_set.push_back(
                Instruction(Syntax(5,{T_sub,T_Ram,T_OpenBrackets,T_Number,T_CloseBrackets}), f, false, 2));
    }
    {
        auto f = [](Program& p) {
            p.tok_instr(); // show
            std::string reg = p.tok_keyword();
            if (reg == "RA") {
                p.program.push_back(std::string("c"));
            } else if (reg == "RB") {
                p.program.push_back(std::string("d"));
            } else {
                p.add_error("Invalid register: " + reg);
            }
        };
        this->instr_set.push_back(
                Instruction(Syntax(2,{T_show,T_Keyword}), f, false, 1));
    }
    {
        auto f = [](Program& p) {
            p.tok_instr(); // Halt
            std::string reg = p.tok_keyword();
            p.program.push_back("F");
        };
        this->instr_set.push_back(
                Instruction(Syntax(1,{T_halt}), f, false, 1));
    }
    {
        auto f = [](Program& p) {
            p.tok_instr(); // show
            p.tok_instr(); // RAM
            p.tok_instr(); // [
            
            auto addr = p.tok_number();
            p.program.push_back(std::format("e{:x}", addr));

            p.tok_instr(); // ]
        };
        this->instr_set.push_back(
                Instruction(Syntax(5,{T_show,T_Ram,T_OpenBrackets,T_Number,T_CloseBrackets}), f, false, 2));
    }

    {
        auto f = [](Program& p) {
            p.tok_instr(); // jump
            p.tok_instr(); // @
            std::string section = p.tok_keyword();
            if (!p.jump_table.contains(section)) {
                p.add_error("Invalid section: " + section);
            }
            int section_addr = p.jump_table[section];
            std::string ret = "b";
            ret += std::format("{:x}", section_addr);
            p.program.push_back(ret);
        };
        this->instr_set.push_back(
                Instruction(Syntax(3,{T_jump,T_SectionAt,T_Keyword}), f, false, 2));
    }
    {
        auto f = [](Program& p) {
            p.tok_instr(); // MOV
            auto reg = p.tok_keyword(); // register
            p.tok_instr(); // ,
            p.tok_instr(); // RAM
            p.tok_instr(); // [
            int addr = p.tok_number(); // address
            p.tok_instr(); // ]
            
            std::string ret; 
            if (reg == "RA") {
                ret += "5";
            } else if (reg == "RB") {
                ret += "7";
            } else {
                p.add_error("Invalid register: " + reg);
            }
            ret += std::format("{:x}", addr);
            p.program.push_back(ret);
        };
        this->instr_set.push_back(
                Instruction(Syntax(7,{T_mov,T_Keyword,T_Comma,T_Ram,T_OpenBrackets,T_Number,T_CloseBrackets}), f, false, 2));
    }

    for (auto& i : this->instr_set) {
        this->grammar.add_entry(i);
    }
}

Parser::~Parser() {
}

bool Parser::pre_compile() {
    std::vector<Token> n_tokens;
    n_tokens = this->grammar.clear(this->tokens);    
    
    std::cout << "------------\n";
    for (auto t : n_tokens) {
        std::cout << t.str << ": " << t.type << '\n';
    }
    std::cout << "------------\n\n";
    
    this->program.tokens = n_tokens;
    this->program.token_ptr = 0;
    this->program.program_ptr = 0;
    this->program.error = false;
    this->program.error_str = "";

    if (!this->grammar.compile(true, this->program)) {
        return false;
    }

    return true;
}

bool Parser::compile() {
    if (!this->pre_compile()) {
        std::cout << "Program compilation failed.\n";
        return false;
    }

    if (!this->grammar.compile(false, this->program)) {
        std::cout << "Program compilation failed.\n";
        return false;
    }
    
    for (auto& i : this->program.instructions) {
        i.process_f(this->program);
    }
    std::string result;
    int size = 0;
    for (auto& i : this->program.program) {
        for (auto c : i) {
            result += c;
            if (!(size % 2))
                result += ' ';
        }
    }
    
    std::cout << "Output: ";
    std::cout << result << '\n';
    
    this->program_result = result;

    return true;
}

bool Parser::compile(std::string file_path) {
    if (!this->compile())
        return false;

    std::ofstream of(file_path, std::ios::out);
    if (!of) {
        std::cout << "Couldn't open " << file_path << " for writing.\n";
        return false;
    }

    of << "v2.0 raw\n";
    
    of << this->program_result;
    
    std::cout << "Result written to " << file_path << '\n';
    of.close();

    return true;
}

std::string Parser::get_error() {
    return this->error;
}
