#include <iostream>
#include <cstdlib>
#include "lexical/LexicalAnalysis.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << "[Program]" << std::endl;
        exit(1);
    }

    try {
        Lexeme lex;
        LexicalAnalysis l(argv[1]);

        while ((lex = l.nextToken()).type > 0) {
            std::cout << lex.str() << std::endl;
        }
        std::cout << lex.str() << std::endl;
        std::cout << std::endl;
        l.showTable();

    } catch (const std::string& error) {
        std::cerr << error << std::endl;
    }
    return 0;
}