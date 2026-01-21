#include "interpreter.h"
#include <iostream>
#include <stdexcept>

double Interpreter::eval(Expr* e) {

    if (auto n = dynamic_cast<NumberExpr*>(e)) return n->value;

    if (auto v = dynamic_cast<VarExpr*>(e)) {
        if (!vars.count(v->name))
            throw std::runtime_error("Undefined variable");
        return vars[v->name];
    }

    if (auto b = dynamic_cast<BinaryExpr*>(e)) {
        double l = eval(b->left);
        double r = eval(b->right);
        switch (b->op) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/': return l / r;
        }
    }

    return 0;
}

bool Interpreter::evalCond(Expr* e) {
    auto c = dynamic_cast<ConditionExpr*>(e);
    return eval(c->left) > eval(c->right);
}

void Interpreter::exec(Stmt* s) {

    if (auto v = dynamic_cast<VarDeclStmt*>(s)) {
        double val = eval(v->value);
        vars[v->name] = v->isFloat ? val : (int)val;
        isFloat[v->name] = v->isFloat;
        return;
    }

    if (auto a = dynamic_cast<AssignStmt*>(s)) {
        if (!vars.count(a->name))
            throw std::runtime_error("Undeclared variable");
        double val = eval(a->value);
        if (!isFloat[a->name] && val != (int)val)
            throw std::runtime_error("Type error");
        vars[a->name] = isFloat[a->name] ? val : (int)val;
        return;
    }

    if (auto p = dynamic_cast<PrintStmt*>(s)) {
        double v = eval(p->value);
        if (v == (int)v) std::cout << (int)v << "\n";
        else std::cout << v << "\n";
        return;
    }

    if (auto i = dynamic_cast<IfStmt*>(s)) {
        if (evalCond(i->condition))
            for (auto st : i->thenBranch) exec(st);
        else
            for (auto st : i->elseBranch) exec(st);
    }
}

void Interpreter::run(Program* p) {
    for (auto s : p->statements)
        exec(s);
}
