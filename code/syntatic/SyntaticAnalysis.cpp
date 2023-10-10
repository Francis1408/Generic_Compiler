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
    if(m_current.type == TT_INT || m_current.type == TT_STRING || m_current.type == TT_FLOAT ) {
        procDecl_list();
    }
    procBody();
    
}
// <decl-list> ::= <decl> “;”{<decl>, “;”}
void SyntaticAnalysis::procDecl_list() {
    procDecl();
    eat(TT_SEMICOLON);
    while (m_current.type == TT_INT || m_current.type == TT_STRING || m_current.type == TT_FLOAT ) {
        procDecl();
        eat(TT_SEMICOLON);
    }

}

// <decl> ::= <type> <ident-list>
void SyntaticAnalysis::procDecl() {
    procType();
    procIdent_list();
}

// <ident-list> ::= identifier {“,” identifier}
void SyntaticAnalysis::procIdent_list() {
    eat(TT_ID);
    while(m_current.type == TT_COMMA) {
        advance();
        eat(TT_ID);
    }
}

// <type> ::= int | string | float
void SyntaticAnalysis::procType() {
    if(m_current.type == TT_INT) {
        eat(TT_INT);
    } else if(m_current.type == TT_STRING) {
        eat(TT_STRING);
    } else if(m_current.type == TT_FLOAT) {
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
    procStmt();
    eat(TT_SEMICOLON);
    while(m_current.type == TT_ID || m_current.type == TT_IF || m_current.type == TT_DO || m_current.type == TT_READ || m_current.type == TT_WRITE) {
        procStmt();
        eat(TT_SEMICOLON);
    }

}

//<stmt> ::= <assign-stmt> | <if-stmt> | <do-stmt> | <read-stmt> | <write-stmt>
void SyntaticAnalysis::procStmt() {
    if(m_current.type == TT_ID) {
        procAssign_stmt();
    } else if(m_current.type == TT_IF) {
        procIf_stmt();
    } else if (m_current.type == TT_DO) {
        procDo_stmt();
    } else if (m_current.type == TT_READ)  {
        procRead_stmt();
    } else if (m_current.type == TT_WRITE) {
        procWrite_stmt();
    } else {
        showError();
    }

}

// <assign-stmt> ::= identifier “=” <simple_expr>
void SyntaticAnalysis::procAssign_stmt() {
    eat(TT_ID);
    eat(TT_ASSIGN);
    procSimple_expr();
}

// <if-stmt> ::= if “(” <condition> “)” “{” <stmt-list> “}” <if-stmt’>
void SyntaticAnalysis::procIf_stmt() {
    eat(TT_IF);
    eat(TT_PAR1);
    procCondition();
    eat(TT_PAR2);
    eat(TT_CHAV1);
    procStmt_list();
    eat(TT_CHAV2);
    procIf_stmt_l();
}

// <if-stmt’> ::= λ | else “{” <stmt-list> “}”
void SyntaticAnalysis::procIf_stmt_l() {

} 

// <condition> ::= <expression>
void SyntaticAnalysis::procCondition() {
    procExpression();
}

// <do-stmt> ::= do “{” <stmt-list> “}” <do-suffix>
void SyntaticAnalysis::procDo_stmt() {
    eat(TT_DO);
    eat(TT_CHAV1);
    procStmt_list();
    eat(TT_CHAV2);
    procDo_suffix();

}

// <do-suffix> ::= while “(” <condition> “)”
void SyntaticAnalysis::procDo_suffix() {
    eat(TT_WHILE);
    eat(TT_PAR1);
    procCondition();
    eat(TT_PAR2);
}

// <read-stmt> ::= read “(” identifier “)”
void SyntaticAnalysis::procRead_stmt() {
    eat(TT_READ);
    eat(TT_PAR1);
    eat(TT_ID);
    eat(TT_PAR2);
}

// <write-stmt> ::= write “(” <writable> “)”
void SyntaticAnalysis::procWrite_stmt() {
    eat(TT_WRITE);
    eat(TT_PAR1);
    procWritable();
    eat(TT_PAR2);
}

// <writable> ::= <simple-expr>
void SyntaticAnalysis::procWritable() {
    procSimple_expr();
}

// <expression>	::= <simple-expr> <expression’>
void SyntaticAnalysis::procExpression() {
    procSimple_expr();
    procExpression_l();
}

// <simple-expr’> ::= <addop> <term> <simple-expr’> | λ
void SyntaticAnalysis::procExpression_l() {

}

// <simple-expr> ::= <term> <simple-expr’>
void SyntaticAnalysis::procSimple_expr() {
    procTerm();
    procSimple_expr_l();
}

// <simple-expr’> ::= <addop> <term> <simple-expr’> | λ
void SyntaticAnalysis::procSimple_expr_l() {

}

// <term>  ::= <factor-a> <term’>
void SyntaticAnalysis::procTerm() {
    procFactor_a();
    procTerm_l();
}

// <term’> ::= <mulop> <factor-a> <term’> | λ
void SyntaticAnalysis::procTerm_l() {
    
}

// <factor-a> ::= <factor> | “!” <facotr>
void SyntaticAnalysis::procFactor_a() {
    if(m_current.type == TT_ID || m_current.type == TT_INTEGER || m_current.type == TT_LITERAL || m_current.type == TT_REAL || m_current.type == TT_PAR1) {
        procFactor();
    } else if(m_current.type == TT_NOT) {
        advance();
        procFactor();
    } else {
        showError();
    }
}

// <factor>	::= identifier | <constant> | “(” <expression> “)”
void SyntaticAnalysis::procFactor() {
    if(m_current.type == TT_ID) {
        advance();
    } else if(m_current.type == TT_INTEGER || m_current.type == TT_LITERAL || m_current.type == TT_REAL) {
        procConstant();
    } else if(m_current.type == TT_PAR1) {
        advance();
        procExpression();
        eat(TT_CHAV2);
    }
}

// <relop> ::= “>” | “>=” | “<” | “<=”  | “!=” | “==”
void SyntaticAnalysis::procRelop() {
    if(m_current.type == TT_EQUAL) {
        eat(TT_EQUAL);
    } else if ( m_current.type == TT_NOT_EQUAL) {
        eat(TT_NOT_EQUAL);
    } else if (m_current.type == TT_LOWER) {
        eat(TT_LOWER);
    } else if (m_current.type == TT_GREATER) {
        eat(TT_GREATER);
    } else if (m_current.type == TT_LESS_EQUAL) {
        eat(TT_LESS_EQUAL);
    } else if ( m_current.type == TT_GREATER_EQUAL) {
        eat(TT_GREATER_EQUAL);
    } else {
        showError();
    }
}

// <addop> ::= “+” | “-” | “||”
void SyntaticAnalysis::procAddop() {
    if(m_current.type == TT_ADD){
        eat(TT_ADD);
    } else if (m_current.type == TT_SUB) {
        eat(TT_SUB);
    } else if (m_current.type == TT_OR ) {
        eat(TT_OR);
    } else {
        showError();
    }
}

// <mulop> ::= “*” | “/” | “&&”
void SyntaticAnalysis::procMulop() {
    if(m_current.type == TT_MUL) {
        eat(TT_MUL);
    } else if (m_current.type == TT_DIV) {
        eat(TT_DIV);
    } else if (m_current.type == TT_AND ) {
        eat(TT_AND);
    } else {
        showError();
    }
}

// <constant> ::= integer_const | literal | real_const
void SyntaticAnalysis::procConstant() {
    if(m_current.type == TT_INTEGER) {
        eat(TT_INTEGER);
    } else if (m_current.type == TT_LITERAL) {
        eat(TT_LITERAL);
    } else if (m_current.type == TT_REAL ) {
        eat(TT_REAL);
    } else {
        showError();
    }
}

