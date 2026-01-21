#pragma once
#include "lexer.h"
#include "ast.h"
#include <vector>

class Parser {
    std::vector<Token> tokens;
    size_t pos = 0;

public:
    Parser(const std::vector<Token>& t);
    Program* parseProgram();

private:
    Stmt* parseStatement();
    Stmt* parseAssignment();
    Stmt* parseIf();

    Expr* parseExpr();
    Expr* parseTerm();
    Expr* parseFactor();
    Expr* parseCondition();

    Token peek();
    Token advance();
    bool match(TokenType t);
};
