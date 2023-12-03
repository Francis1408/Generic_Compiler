#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"

class ExprType;
class IdentList;
class ReadCommand;
class RelopExpr;
class MulopExpr;
class AddopExpr;
class FactorExpr;
class Term_L_Expr;
class Term_Expr;
class Simple_Expr_L;
class SyntaticAnalysis {
    public:
        SyntaticAnalysis(LexicalAnalysis& lex);
        virtual ~SyntaticAnalysis();

        void start();

    private:
        LexicalAnalysis& m_lex;
        Lexeme m_current;

        void advance();
        void eat(enum TokenType type);
        void showError();

        void procProgram();
        void procDecl_list();
        void procDecl();
        IdentList* procIdent_list();
        ExprType* procType();
        void procBody();
        void procStmt_list();
        void procStmt();
        void procAssign_stmt();
        void procIf_stmt();
        void procIf_stmt_l(); 
        void procCondition();
        void procDo_stmt();
        void procDo_suffix();
        ReadCommand* procRead_stmt();
        void procWrite_stmt();
        void procWritable();
        void procExpression();
        void procExpression_l();
        void procSimple_expr();
        Simple_Expr_L* procSimple_expr_l();
        Term_Expr* procTerm();
        Term_L_Expr* procTerm_l();
        FactorExpr* procFactor_a();
        FactorExpr* procFactor();
        RelopExpr* procRelop();
        AddopExpr* procAddop();
        MulopExpr* procMulop();
        ExprType* procConstant();
};


#endif