#pragma once

#include "alloc.hpp"
#include "token.hpp"
#include <variant>

namespace ast {

struct NodeExpr;

struct NodeFactorParen {
    const Token* tok_left_paren;
    NodeExpr* expr;
    const Token* tok_right_paren;
};

struct NodeFactorPos {
    const Token* tok_num;
};

struct NodeFactorNeg {
    const Token* tok_sub;
    const Token* tok_num;
};

struct NodeFactorIdent {
    const Token* tok_ident;
};

struct NodeFactor {
    std::variant<NodeFactorParen*, NodeFactorPos*, NodeFactorNeg*, NodeFactorIdent*> var;
};

struct NodeCmpPred;

struct NodeCmpPredLt {
    const Token* tok_lt;
    NodeFactor* factor;
    std::optional<NodeCmpPred*> cmp_pred;
};

struct NodeCmpPredGt {
    const Token* tok_gt;
    NodeFactor* factor;
    std::optional<NodeCmpPred*> cmp_pred;
};

struct NodeCmpPredLte {
    const Token* tok_lte;
    NodeFactor* factor;
    std::optional<NodeCmpPred*> cmp_pred;
};

struct NodeCmpPredGte {
    const Token* tok_gte;
    NodeFactor* factor;
    std::optional<NodeCmpPred*> cmp_pred;
};

struct NodeCmpPred {
    std::variant<NodeCmpPredLt*, NodeCmpPredGt*, NodeCmpPredLte*, NodeCmpPredGte*> var;
};

struct NodeCmp {
    NodeFactor* factor;
    std::optional<NodeCmpPred*> cmp_pred;
};

struct NodeTermPred;

struct NodeTermPredMulti {
    const Token* tok_multi;
    NodeCmp* cmp;
    std::optional<NodeTermPred*> term_pred;
};

struct NodeTermPredDiv {
    const Token* tok_div;
    NodeCmp* cmp;
    std::optional<NodeTermPred*> term_pred;
};

struct NodeTermPred {
    std::variant<NodeTermPredMulti*, NodeTermPredDiv*> var;
};

struct NodeTerm {
    NodeCmp* cmp;
    std::optional<NodeTermPred*> term_pred;
};

struct NodeExprPred;

struct NodeExprPredAdd {
    const Token* tok_add;
    NodeTerm* term;
    std::optional<NodeExprPred*> expr_pred;
};

struct NodeExprPredSub {
    const Token* tok_sub;
    NodeTerm* term;
    std::optional<NodeExprPred*> expr_pred;
};

struct NodeExprPred {
    std::variant<NodeExprPredAdd*, NodeExprPredSub*> var;
};

struct NodeExpr {
    NodeTerm* term;
    std::optional<NodeExprPred*> expr_pred;
};

struct NodeStmt;

struct NodeStmtPred {
    NodeStmt* stmt;
};

struct NodeLet {
    const Token* tok_let;
    const Token* tok_ident;
    const Token* tok_eq;
    NodeExpr* expr;
    const Token* tok_semi;
};

struct NodeStmtLet {
    NodeLet* let;
    std::optional<NodeStmtPred*> stmt_pred;
};

struct NodeEq {
    const Token* tok_ident;
    const Token* tok_eq;
    NodeExpr* expr;
    const Token* tok_semi;
};

struct NodeStmtEq {
    NodeEq* eq;
    std::optional<NodeStmtPred*> stmt_pred;
};

struct NodePrint {
    const Token* tok_print;
    const Token* tok_left_paren;
    NodeExpr* expr;
    const Token* tok_right_paren;
    const Token* tok_semi;
};

struct NodeStmtPrint {
    NodePrint* print;
    std::optional<NodeStmtPred*> stmt_pred;
};

struct NodeStmt {
    std::variant<NodeStmtPrint*, NodeStmtLet*, NodeStmtEq*> var;
};

// TODO
// void print_ast(const NodeBase& node, int level = 0)
//{
//    std::string bars;
//    for (int i = 0; i < level; i++) {
//        bars.append("| ");
//    }
//    std::cout << bars << to_string(node.type) << "\n";
//    bars.append("| ");
//    for (const NodeBase& child : node.children) {
//        if (child.type == ASTNodeType::terminal) {
//            std::cout << bars << child.token->value << "\n";
//        }
//        else {
//            print_ast(child, level + 1);
//        }
//    }
//}
}