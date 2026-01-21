#include <fstream>
#include <iostream>
#include <vector>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: bangla <file.bng>\n";
        return 1;
    }

    std::ifstream f(argv[1]);
    if (!f) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    std::string src((std::istreambuf_iterator<char>(f)),
                     std::istreambuf_iterator<char>());

    Lexer lex(src);
    std::vector<Token> tokens;
    while (true) {
        Token t = lex.nextToken();
        tokens.push_back(t);
        if (t.type == TokenType::END) break;
    }

    Parser parser(tokens);
    Program* program = parser.parseProgram();

    Interpreter interp;
    interp.run(program);
}
