#include <iostream>
#include <fstream>

#include "lexer.hpp"
#include "parser.hpp"

int main(int argc, const char** argv) {
    if (argc < 2) {
        std::cout << "Uso: bcpu-asm (nome do arquivo de entrada)\n";
        return 1;
    }
    else {
        std::string content;
        std::string buf;

        std::ifstream fs(argv[1], std::ios_base::in);
        
        while (fs) {
            std::getline(fs, buf);
            content+=buf+'\n';
        }

        fs.close(); 
        std::cout << "------\n\n" << content << "-----\n\n"; 
        std::vector<Token> tokens = lexer_process(content);
        for (auto t : tokens) {
            std::cout << t.str << ": " << t.type << '\n';
        }

        Parser parser(tokens);
        bool res;
        if (argc == 3)
            res = parser.compile(argv[2]);
        else
            res = parser.compile();

        if (!res) {
            std::cout << "Erro ao processar o codigo: " << parser.get_error() << '\n';
        }
    }

    return 0;
}
