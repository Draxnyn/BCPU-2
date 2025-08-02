#include <stdexcept>
#include <iostream>

#include "lexer.hpp"

// Separation token
bool sep_token(char c) {
    return c == '\n' || c == ' ' || c == ',' || c == ':' || c == '[' || c == ']' || c == '@';
}

std::vector<Token> lexer_process(std::string file) {
    std::vector<Token> list;
    
    // Current token string being formed
    std::string curr_t;
    // If the last token expects a 1: keyword or a 2: number, or 0 for nothing
    int l_token_expect = 0;
    bool ignore = false;
    for (auto i = 0; i < file.size(); i++) {
        auto c = file[i];
        
        bool eof = i == file.size()-1;
        // End of token
        bool eot = sep_token(c) || eof;
        
        if (c == '#') {
            ignore = true;
        }
        if (ignore) {
            if (c == '\n')
                ignore = false;
            else
                continue;
        }
         
        if (!eot) {
            curr_t += c;
        } else {
            // This can happen when two separation-tokens are together like ", "
            if (curr_t != "") {
                // Process the token being analysed before processing the end of token
                // character.
                // If it's forced to expect a token
                // NOTE: IT'S NEVER EXPECTED ANY TOKEN IN THE LEXER STEP YET.
                if(l_token_expect) {
                    Token t;
                    t.str = curr_t;
                    // Expecting a keyword
                    if (l_token_expect == 1) {
                        t.valid = true;
                        t.type = T_Keyword;
                        t.str_data = curr_t;
                    } else { // Expecting a number
                        t.valid = true;
                        t.type = T_Number;
                        try {
                            t.int_data = std::stoi(curr_t);
                        } catch (const std::invalid_argument& e) {
                            std::cerr << "Expected number. Got: " << curr_t << '\n';
                            t.valid = false;
                        }
                    }
                    list.push_back(t);
                    l_token_expect = 0;
                } else {
                    Token t;
                    t.str = curr_t;
                    t.valid = true;
                    l_token_expect = 0;
                    if (curr_t == "add")
                    {
                        t.type = T_add;
                    }
                    else if (curr_t == "sub")
                    {
                        t.type = T_sub;
                    }
                    else if (curr_t == "set")
                    {
                        t.type = T_set;
                    }
                    else if (curr_t == "mov")
                    {
                        t.type = T_mov;
                    }
                    else if (curr_t == "jump")
                    {
                        t.type = T_jump;
                    }
                    else if (curr_t == "halt")
                    {
                        t.type = T_halt;
                    }
                    else if (curr_t == "RAM")
                    {
                        t.type = T_Ram;
                    }
                    else if (curr_t == "show")
                    {
                        t.type = T_show;
                    }
                    else
                    {
                        // If it starts with a digit, it must be
                        // a number.
                        // TODO: FIX THIS MESS!!
                        t.type = T_Number;
                        if (curr_t[0] >= 48 && curr_t[0] <= 57 &&
                            curr_t.size() == 1) {
                            t.int_data = (int)(curr_t[0])-48;
                        } else if
                            (curr_t[0] >= 97 && curr_t[0] <= 102 && 
                             curr_t.size() == 1) {
                            t.int_data = (int)(curr_t[0])-87;
                        } else if 
                            (curr_t[0] >= 65 && curr_t[0] <= 70 &&
                             curr_t.size() == 1) {
                            t.int_data = (int)(curr_t[0])-55;
                        }
                        else {
                            t.type = T_Keyword;
                            t.str_data = curr_t;
                        }
                    }
                    list.push_back(t);
                }
            }
            // Discards the token string that's being analysed. 
            // Here what will be analysed is only the current
            // character
            curr_t = "";
            Token t;
            t.str = c;
            t.valid = true;
            l_token_expect = 0;
            // Process end of token's character
            switch (c) {
                case '\n':
                {
                    t.type = T_NewLine;
                    break;
                }
                case ',':
                {
                    t.type = T_Comma;
                    break;
                }
                case ':':
                {
                    t.type = T_TwoDots;
                    break;
                }
                case '[':
                {
                    t.type = T_OpenBrackets;
                    break;
                }
                case ']':
                {
                    t.type = T_CloseBrackets;
                    break;
                }
                case '@':
                {
                    t.type = T_SectionAt;
                    break;
                }
                case ' ':
                {
                    t.type = T_Space;
                    break;
                }
                default:
                {
                    t.type = T_Keyword;
                    t.str = std::to_string(c);
                    break;
                }
            }
            // If it's eof, there's no more character to analyse.
            if (!eof)
                list.push_back(t);
        }

    }

    return list;
}
