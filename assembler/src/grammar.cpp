#include <iostream>
#include "grammar.hpp"

std::vector<Token> Grammar::clear(const std::vector<Token>& tokens) {
    // Note: This isn't syntax-generic, and these tokens may be useful somewhere.
    std::vector<Token> ret;
    
    for (auto t : tokens) {
        if (t.type != T_NewLine && t.type != T_Space) {
            ret.push_back(t);
        }
    }

    return ret;
}

bool Grammar::compile(bool pre_compilation, Program& program) {
    program.instructions.clear();
    // TODO: THIS FUNCTION IS TOO EXPENSIVE!! IT CHECKS EVERY ENTRY FOR EVERY TOKEN
    size_t pointer = 0;
    while (pointer < program.tokens.size()) {
        bool one_match = false;
        for (auto& instr : this->entries) {
            auto& synt = instr.syntax;
            // NOTE: Tries matching the program tokens with instr syntax. 
            // This may be error prone.
            auto p = synt.match(program.tokens, pointer);
            if (p != pointer) {
                pointer = p;
                one_match = true;
                if (instr.pre_compile && pre_compilation)
                    instr.process_f(program);
                program.program_ptr += instr.instr_size;
                // NOTE: IF A INSTRUCTION VARIES ON TOKEN LENGTH, THIS MAY FAIL.
                program.token_ptr += synt.expect.size();

                program.instructions.push_back(instr);
                break;
            }
        }
        if (!one_match) {
            std::cout << "Invalid token: " << program.tokens[pointer].str << '\n';
            return false;
        }        
    }

    program.program_ptr = 0;
    program.token_ptr = 0;
    program.program.clear(); 

    return true;
}

void Grammar::add_entry(Instruction entry) {
    this->entries.push_back(entry);
}
