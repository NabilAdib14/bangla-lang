#include "parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& t) : tokens(t) {}

Token Parser::peek() { return tokens[pos]; }
Token Parser::advance() { return tokens[pos++]; }

bool Parser::match(TokenType t) {
    if (peek().type == t) {
        advance();
        return true;
    }
    return false;
}

Program* Parser::parseProgram() {
    Program* p = new Program();
    while (peek().type != TokenType::END)
        p->statements.push_back(parseStatement());
    return p;
}

Stmt* Parser::parseStatement() {

    if (peek().type == TokenType::INTEGER || peek().type == TokenType::FLOAT) {
        advance();
        bool isFloat = tokens[pos - 1].type == TokenType::FLOAT;

        Token name = advance();
        if (name.type != TokenType::IDENT)
            throw std::runtime_error("Expected variable name");

        if (!match(TokenType::TE))
            throw std::runtime_error("Expected te");

        return new VarDeclStmt(name.text, isFloat, parseExpr());
    }

    if (peek().type == TokenType::IDENT && tokens[pos + 1].type == TokenType::ASSIGN)
        return parseAssignment();

    if (match(TokenType::DEKHAO)) {
        match(TokenType::LPAREN);
        Expr* e = parseExpr();
        match(TokenType::RPAREN);
        return new PrintStmt(e);
    }

    if (peek().type == TokenType::JODI)
        return parseIf();

    throw std::runtime_error("Unknown statement");
}

Stmt* Parser::parseAssignment() {
    std::string name = advance().text;
    match(TokenType::ASSIGN);
    return new AssignStmt(name, parseExpr());
}

Expr* Parser::parseCondition() {
    Expr* l = parseExpr();
    if (!match(TokenType::GT))
        throw std::runtime_error("Expected >");
    Expr* r = parseExpr();
    return new ConditionExpr(l, r);
}

Stmt* Parser::parseIf() {
    advance();
    match(TokenType::LPAREN);
    Expr* cond = parseCondition();
    match(TokenType::RPAREN);

    match(TokenType::LBRACE);
    std::vector<Stmt*> thenS;
    while (!match(TokenType::RBRACE))
        thenS.push_back(parseStatement());

    std::vector<Stmt*> elseS;
    if (match(TokenType::NAHOLE)) {
        match(TokenType::LBRACE);
        while (!match(TokenType::RBRACE))
            elseS.push_back(parseStatement());
    }

    IfStmt* s = new IfStmt();
    s->condition = cond;
    s->thenBranch = thenS;
    s->elseBranch = elseS;
    return s;
}

Expr* Parser::parseExpr() {
    Expr* l = parseTerm();
    while (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS) {
        char op = advance().text[0];
        l = new BinaryExpr(op, l, parseTerm());
    }
    return l;
}

Expr* Parser::parseTerm() {
    Expr* l = parseFactor();
    while (peek().type == TokenType::STAR || peek().type == TokenType::SLASH) {
        char op = advance().text[0];
        l = new BinaryExpr(op, l, parseFactor());
    }
    return l;
}

Expr* Parser::parseFactor() {
    Token t = advance();
    if (t.type == TokenType::NUMBER) return new NumberExpr(std::stod(t.text));
    if (t.type == TokenType::IDENT) return new VarExpr(t.text);
    if (t.type == TokenType::LPAREN) {
        Expr* e = parseExpr();
        match(TokenType::RPAREN);
        return e;
    }
    throw std::runtime_error("Invalid expression");
}
