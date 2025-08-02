#pragma once

#include <vector>

#include "token.hpp"

struct Syntax {
    Syntax(int l, const std::vector<TType>& tks);
    std::vector<TType> expect;
    // Size limit of the syntax, for example the max number of tokenspossible for a instruction, this may be a bit limiting for now.
    int limit;
    
    // Starts reading from tokens at pointer. If invalid, return pointer, otherwise returns the pointer after the last token of the syntax.
    size_t match(const std::vector<Token>& tokens, size_t pointer);
};
