#include <iostream>

#include "syntax.hpp"

Syntax::Syntax(int l, const std::vector<TType>& tks) {
    this->limit = l;
    this->expect = tks;
}

size_t Syntax::match(const std::vector<Token>& tokens, size_t pointer) {
    auto i = pointer;
    bool invalid = false;
    while (i - pointer < this->limit && !invalid && i < tokens.size()) {
        if (tokens[i].type != this->expect[i-pointer]) {
            invalid = true;
            break;
        }
        i++;
    }

    
    if (invalid)
        return pointer;
//    else
//        std::cout << "Valid syntax: " << tokens[pointer].str << "!\n";
    return i;
}
