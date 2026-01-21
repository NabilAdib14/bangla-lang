#pragma once
#include "ast.h"
#include <unordered_map>
#include <string>

class Interpreter {
    std::unordered_map<std::string, double> vars;
    std::unordered_map<std::string, bool> isFloat;

public:
    void run(Program* p);

private:
    void exec(Stmt* s);
    double eval(Expr* e);
    bool evalCond(Expr* e);
};
