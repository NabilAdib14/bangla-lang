#pragma once
#include <string>

enum class TokenType {
    INTEGER, FLOAT, TE, DEKHAO, JODI, NAHOLE,
    IDENT, NUMBER,
    PLUS, MINUS, STAR, SLASH,
    LPAREN, RPAREN, LBRACE, RBRACE,
    GT, ASSIGN,
    END
};

struct Token {
    TokenType type;
    std::string text;
};

class Lexer {
    std::string source;
    size_t pos = 0;

public:
    Lexer(const std::string& src);
    Token nextToken();
};
