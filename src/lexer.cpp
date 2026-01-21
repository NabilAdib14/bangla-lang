#include "lexer.h"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string& src) : source(src) {}

char peekChar(const std::string& s, size_t p) {
    return p >= s.size() ? '\0' : s[p];
}

Token Lexer::nextToken() {

    while (isspace(peekChar(source, pos))) pos++;

    char c = peekChar(source, pos);
    if (c == '\0') return {TokenType::END, ""};

    if (isalpha(c) || c == '_') {
        std::string id;
        while (isalnum(peekChar(source, pos)) || peekChar(source, pos) == '_')
            id += source[pos++];

        if (id == "integer") return {TokenType::INTEGER, id};
        if (id == "float") return {TokenType::FLOAT, id};
        if (id == "te") return {TokenType::TE, id};
        if (id == "dekhao") return {TokenType::DEKHAO, id};
        if (id == "jodi") return {TokenType::JODI, id};
        if (id == "nahole") return {TokenType::NAHOLE, id};

        return {TokenType::IDENT, id};
    }

    if (isdigit(c)) {
        std::string num;
        while (isdigit(peekChar(source, pos)) || peekChar(source, pos) == '.')
            num += source[pos++];
        return {TokenType::NUMBER, num};
    }

    pos++;
    switch (c) {
        case '+': return {TokenType::PLUS, "+"};
        case '-': return {TokenType::MINUS, "-"};
        case '*': return {TokenType::STAR, "*"};
        case '/': return {TokenType::SLASH, "/"};
        case '(': return {TokenType::LPAREN, "("};
        case ')': return {TokenType::RPAREN, ")"};
        case '{': return {TokenType::LBRACE, "{"};
        case '}': return {TokenType::RBRACE, "}"};
        case '>': return {TokenType::GT, ">"};
        case '=': return {TokenType::ASSIGN, "="};
    }

    throw std::runtime_error("Unknown character");
}
