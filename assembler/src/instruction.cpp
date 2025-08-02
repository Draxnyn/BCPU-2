#include <instruction.hpp>

void Program::tok_instr() {
    this->token_ptr++;
}

std::string Program::tok_keyword() {
    return this->tokens[this->token_ptr++].str_data;
}

int Program::tok_number() {
    return this->tokens[this->token_ptr++].int_data;
}

void Program::add_error(std::string str) {
    this->error = true;
    this->error_str += str + "\n";
}

//Instruction::Instruction(Syntax synt, p_ftype p_func)
//    : syntax(synt), process_f(p_func) {
//}
