#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "SyntaticAnalysis.h"


SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex) :
    m_lex(lex), m_current(lex.nextToken()) {

}
SyntaticAnalysis::~SyntaticAnalysis() {

}

void SyntaticAnalysis::start() {

}

void SyntaticAnalysis::advance() {
    m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(enum TokenType type) {
    std::cout << "Expected (..., " << tt2str(type) 
              << "), found (\"" << m_current.token << "\", " 
              << tt2str(m_current.type) << ")";
    if(type ==  m_current.type) {
        advance();
    } else {
        showError();
    }
}

void SyntaticAnalysis::showError() {
    std::cout << std::setw(2) << std::setfill('0') << m_lex.line() << std::endl;

    switch(m_current.type) {
        case TT_INVALID_TOKEN:
        std::cout << "Lexema inválido [" << m_current.token << "]" << std::endl;
        case TT_UNEXPECTED_EOF:
        case TT_END_OF_FILE:
            std::cout << "Fim de arquivo inesperado" << std::endl;
            break;
        default:
            std::cout << "Lexema não esperado [" << m_current.token << "]" << std::endl;
            break;         
    }
    
    exit(1);
}

// <program> ::= class indentifier [<decl-list>] <body>
void SyntaticAnalysis::procProgram() {
    eat(TT_CLASS);
    eat(TT_ID);
    

}
// <decl-list> ::= <decl> “;”{<decl>, “;”}
void SyntaticAnalysis::procDecl_list() {

}

// <decl> ::= <type> <ident-list>
void SyntaticAnalysis::procDecl() {

}

// <ident-list> ::= identifier {“,” identifier}
void SyntaticAnalysis::procIdent_list() {

}

// <type> ::= int | string | float
void SyntaticAnalysis::procType() {
    if(m_current.type == TT_INT) {
        eat(TT_INT);
    } else if(m_current.type == TT_STRING) {
        eat(TT_STRING);
    } else if(m_current.type == TT_FLOAT){
        eat(TT_FLOAT);
    } else {
        showError();
    }

}

// <body> ::= “{” <stmt-list> “}”
void SyntaticAnalysis::procBody() {
     eat(TT_CHAV1);
     procStmt_list();
     eat(TT_CHAV2);

}

// <stmt-list> ::=  <stmt> “;” {<stmt> “;”}
void SyntaticAnalysis::procStmt_list() {

}

//<stmt> ::= <assign-stmt> | <if-stmt> | <do-stmt> | <red-stmt> | <write-stmt>
void SyntaticAnalysis::procStmt() {

}

// <assign-stmt> ::= identifier “=” <simple_expr>
void SyntaticAnalysis::procAssign_stmt() {

}

// <if-stmt> ::= if “(” <condition> “)” “{” <stmt-list> “}” <if-stmt’>
void SyntaticAnalysis::procIf_stmt() {

}

// <if-stmt’> ::= λ | else “{” <stmt-list> “}”
void SyntaticAnalysis::procIf_stmt_l() {

} 

// <condition> ::= <expression>
void SyntaticAnalysis::procCondition() {

}

// <do-stmt> ::= do “{” <stmt-list> “}” <do-suffix>
void SyntaticAnalysis::procDo_stmt() {

}

// <do-suffix> ::= while “(” <condition> “)”
void SyntaticAnalysis::procDo_suffix() {

}

// <read-stmt> ::= read “(” identifier “)”
void SyntaticAnalysis::procRead_stmt() {

}

// <write-stmt> ::= write “(” <writable> “)”
void SyntaticAnalysis::procWrite_stmt() {

}

// <writable> ::= <simple-expr>
void SyntaticAnalysis::procWritable() {

}

// <expression>	::= <simple-expr> <expression’>
void SyntaticAnalysis::procExpression() {

}

// <simple-expr’> ::= <addop> <term> <simple-expr’> | λ
void SyntaticAnalysis::procExpression_l() {

}

// <simple-expr> ::= <term> <simple-expr’>
void SyntaticAnalysis::procSimple_expr() {

}

// <simple-expr’> ::= <addop> <term> <simple-expr’> | λ
void SyntaticAnalysis::procSimple_expr_l() {

}

// <term>  ::= <factor-a> <term’>
void SyntaticAnalysis::procTerm() {

}

// <term’> ::= <mulop> <factor-a> <term’> | λ
void SyntaticAnalysis::procTerm_l() {

}

// <factor-a> ::= <factor> | “!” <facotr>
void SyntaticAnalysis::procFactor_a() {

}

// <factor>	::= identifier | <constant> | “(” <expression> “)”
void SyntaticAnalysis::procFactor() {

}

// <relop> ::= “>” | “>=” | “<” | “<=”  | “!=” | “==”
void SyntaticAnalysis::procRelop() {

}

// <addop> ::= “+” | “-” | “||”
void SyntaticAnalysis::procAddop() {

}

// <mulop> ::= “*” | “/” | “&&”
void SyntaticAnalysis::procMulop() {

}

// <constant> ::= integer_const | literal | real_const
void SyntaticAnalysis::procConstant() {

}

