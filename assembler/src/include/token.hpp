#pragma once

#include <string>

enum TType {
    T_NewLine      = 1,
    T_Comma        = 2,
    T_TwoDots      = 3,
    T_Keyword      = 4,
    T_OpenBrackets = 5,
    T_CloseBrackets= 6,
    T_SectionAt    = 7,
    T_Number       = 8,
    T_Space        = 9,
    T_Ram          = 10,
    T_Comment      = 11,
    T_set          = 12,
    T_mov          = 13,
    T_add          = 14,
    T_sub          = 15,
    T_jump         = 16,
    T_halt         = 17,
    T_show         = 18,
};

struct Token {
    TType type;
    std::string str_data;
    int int_data;
    std::string str;
    bool valid;
};
