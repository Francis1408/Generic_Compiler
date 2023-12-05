#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"

class ExprType;
class IdentList;
class ReadCommand;
class WriteCommand;
class AssignCommand;
class IfCommand;
class DoSuffixCommand;
class DoCommand;
class Statement;
class StatementList;
class RelopExpr;
class MulopExpr;
class AddopExpr;
class FactorExpr;
class Term_L_Expr;
class Term_Expr;
class Simple_Expr_L;
class Simple_Expr;
class Expression_L;
class Expression;
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
        StatementList* procStmt_list();
        Statement* procStmt();
        AssignCommand* procAssign_stmt();
        IfCommand* procIf_stmt();
        IfCommand* procIf_stmt_l(); 
        Expression* procCondition();
        DoCommand* procDo_stmt();
        DoSuffixCommand* procDo_suffix();
        ReadCommand* procRead_stmt();
        WriteCommand* procWrite_stmt();
        Simple_Expr* procWritable();
        Expression* procExpression();
        Expression_L* procExpression_l();
        Simple_Expr* procSimple_expr();
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