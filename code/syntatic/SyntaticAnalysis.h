#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"

class ExprType;
class IdentList;
class ReadCommand;
class RelopExpr;
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
        void procSimple_expr_l();
        void procTerm();
        void procTerm_l();
        void procFactor_a();
        void procFactor();
        RelopExpr* procRelop();
        void procAddop();
        void procMulop();
        ExprType* procConstant();
};


#endif