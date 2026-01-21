#pragma once
#include <string>
#include <vector>

struct Expr {
    virtual ~Expr() = default;
};

struct NumberExpr : Expr {
    double value;
    NumberExpr(double v) : value(v) {}
};

struct VarExpr : Expr {
    std::string name;
    VarExpr(const std::string& n) : name(n) {}
};

struct BinaryExpr : Expr {
    char op;
    Expr* left;
    Expr* right;
    BinaryExpr(char o, Expr* l, Expr* r) : op(o), left(l), right(r) {}
};

struct ConditionExpr : Expr {
    Expr* left;
    Expr* right;
    ConditionExpr(Expr* l, Expr* r) : left(l), right(r) {}
};

struct Stmt {
    virtual ~Stmt() = default;
};

struct VarDeclStmt : Stmt {
    std::string name;
    bool isFloat;
    Expr* value;
    VarDeclStmt(const std::string& n, bool f, Expr* v)
        : name(n), isFloat(f), value(v) {}
};

struct AssignStmt : Stmt {
    std::string name;
    Expr* value;
    AssignStmt(const std::string& n, Expr* v) : name(n), value(v) {}
};

struct PrintStmt : Stmt {
    Expr* value;
    PrintStmt(Expr* v) : value(v) {}
};

struct IfStmt : Stmt {
    Expr* condition;
    std::vector<Stmt*> thenBranch;
    std::vector<Stmt*> elseBranch;
};

struct Program {
    std::vector<Stmt*> statements;
};
