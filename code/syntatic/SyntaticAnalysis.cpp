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
    procProgram();
    eat(TT_END_OF_FILE);
}

void SyntaticAnalysis::advance() {
    m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(enum TokenType type) {
    std::cout << "Expected (..., " << tt2str(type) 
              << "), found (\"" << m_current.token << "\", " 
              << tt2str(m_current.type) << ")" << std::endl ;
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
    //std::cout << "ENTROU EM <program>" << std::endl;
    eat(TT_CLASS);
    eat(TT_ID);
    if(m_current.type == TT_INT || m_current.type == TT_STRING || m_current.type == TT_FLOAT ) {
        procDecl_list();
    }
    procBody();
    
}
// <decl-list> ::= <decl> “;”{<decl>, “;”}
void SyntaticAnalysis::procDecl_list() {
    //std::cout << "ENTROU EM <decl-list>" << std::endl;
    procDecl();
    eat(TT_SEMICOLON);
    while (m_current.type == TT_INT || m_current.type == TT_STRING || m_current.type == TT_FLOAT ) {
        procDecl();
        eat(TT_SEMICOLON);
    }

}

// <decl> ::= <type> <ident-list>
void SyntaticAnalysis::procDecl() {
    //std::cout << "ENTROU EM <decl>" << std::endl;
    procType();
    procIdent_list();
}

// <ident-list> ::= identifier {“,” identifier}
void SyntaticAnalysis::procIdent_list() {
    //std::cout << "ENTROU EM <ident-list>" << std::endl;
    eat(TT_ID);
    while(m_current.type == TT_COMMA) {
        advance();
        eat(TT_ID);
    }
}

// <type> ::= int | string | float
void SyntaticAnalysis::procType() {
    //std::cout << "ENTROU EM <type>" << std::endl;
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
   //std::cout << "ENTROU EM <body>" << std::endl; 
    eat(TT_CHAV1);
    procStmt_list();
    eat(TT_CHAV2);

}

// <stmt-list> ::=  <stmt> “;” {<stmt> “;”}
void SyntaticAnalysis::procStmt_list() {
    //std::cout << "ENTROU EM <stmt-list>" << std::endl;
    procStmt();
    eat(TT_SEMICOLON);
    while(m_current.type == TT_ID || m_current.type == TT_IF || m_current.type == TT_DO || m_current.type == TT_READ || m_current.type == TT_WRITE) {
        procStmt();
        eat(TT_SEMICOLON);
    }

}

//<stmt> ::= <assign-stmt> | <if-stmt> | <do-stmt> | <read-stmt> | <write-stmt>
void SyntaticAnalysis::procStmt() {
    //std::cout << "ENTROU EM <stmt>" << std::endl;
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
    //std::cout << "ENTROU EM <assign-stmt>" << std::endl;
    eat(TT_ID);
    eat(TT_ASSIGN);
    procSimple_expr();
}

// <if-stmt> ::= if “(” <condition> “)” “{” <stmt-list> “}” <if-stmt’>
void SyntaticAnalysis::procIf_stmt() {
    //std::cout << "ENTROU EM <if-stmt>" << std::endl;
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
    //std::cout << "ENTROU EM <if-stmt'>" << std::endl;
    if(m_current.type == TT_ELSE) {
        advance();
        eat(TT_CHAV1);
        procStmt_list();
        eat(TT_CHAV2);
    } else if(m_current.type == TT_SEMICOLON) {
        // λ
    } else {
        showError();
    }
} 

// <condition> ::= <expression>
void SyntaticAnalysis::procCondition() {
    std::cout << "ENTROU EM <condition>" << std::endl;
    procExpression();
}

// <do-stmt> ::= do “{” <stmt-list> “}” <do-suffix>
void SyntaticAnalysis::procDo_stmt() {
    //std::cout << "ENTROU EM <do-stmt>" << std::endl;
    eat(TT_DO);
    eat(TT_CHAV1);
    procStmt_list();
    eat(TT_CHAV2);
    procDo_suffix();

}

// <do-suffix> ::= while “(” <condition> “)”
void SyntaticAnalysis::procDo_suffix() {
   //std::cout << "ENTROU EM <do-suffix>" << std::endl;
    eat(TT_WHILE);
    eat(TT_PAR1);
    procCondition();
    eat(TT_PAR2);
}

// <read-stmt> ::= read “(” identifier “)”
void SyntaticAnalysis::procRead_stmt() {
    //std::cout << "ENTROU EM <read-stmt>" << std::endl;
    eat(TT_READ);
    eat(TT_PAR1);
    eat(TT_ID);
    eat(TT_PAR2);
}

// <write-stmt> ::= write “(” <writable> “)”
void SyntaticAnalysis::procWrite_stmt() {
    //std::cout << "ENTROU EM <write-stmt>" << std::endl;
    eat(TT_WRITE);
    eat(TT_PAR1);
    procWritable();
    eat(TT_PAR2);
}

// <writable> ::= <simple-expr>
void SyntaticAnalysis::procWritable() {
    //std::cout << "ENTROU EM <writable>" << std::endl;
    procSimple_expr();
}

// <expression>	::= <simple-expr> <expression’>
void SyntaticAnalysis::procExpression() {
   // std::cout << "ENTROU EM <expression>" << std::endl;
    procSimple_expr();
    procExpression_l();
}

// <expression’>	::= λ | <relop> <simple-expr>
void SyntaticAnalysis::procExpression_l() {
    //std::cout << "ENTROU EM <expression'>" << std::endl;
    if(m_current.type == TT_NOT_EQUAL || m_current.type == TT_GREATER || 
       m_current.type == TT_GREATER_EQUAL || m_current.type == TT_LOWER || m_current.type == TT_LESS_EQUAL || 
       m_current.type == TT_EQUAL) {
        procRelop();
        procSimple_expr();
    }
    else if(m_current.type == TT_PAR2) {
        // λ
    } else {
        showError();
    }
}


// <simple-expr> ::= <term> <simple-expr’>
void SyntaticAnalysis::procSimple_expr() {
    ///std::cout << "ENTROU EM <simple-expr>" << std::endl;
    procTerm();
    procSimple_expr_l();
}

// <simple-expr’> ::= <addop> <term> <simple-expr’> | λ
void SyntaticAnalysis::procSimple_expr_l() {
    //std::cout << "ENTROU EM <simple-expr'>" << std::endl;
    if(m_current.type ==  TT_ADD || m_current.type == TT_SUB || m_current.type == TT_OR) {
        procAddop();
        procTerm();
        procSimple_expr_l();
    } else if(m_current.type == TT_PAR2 || m_current.type == TT_SEMICOLON || m_current.type == TT_NOT_EQUAL || m_current.type == TT_GREATER || 
              m_current.type == TT_GREATER_EQUAL || m_current.type == TT_LOWER || m_current.type == TT_LESS_EQUAL || 
              m_current.type == TT_EQUAL) {
        // λ
    } else {
        showError();
    }
}

// <term>  ::= <factor-a> <term’>
void SyntaticAnalysis::procTerm() {
    //std::cout << "ENTROU EM <term>" << std::endl;
    procFactor_a();
    procTerm_l();
}

// <term’> ::= <mulop> <factor-a> <term’> | λ
void SyntaticAnalysis::procTerm_l() {
    //std::cout << "ENTROU EM <term'>" << std::endl;
    if(m_current.type ==  TT_MUL || m_current.type == TT_DIV || m_current.type == TT_AND) {
        procMulop();
        procFactor_a();
        procTerm_l();
    } else if(m_current.type == TT_ADD || m_current.type == TT_SUB || m_current.type == TT_OR || 
              m_current.type == TT_SEMICOLON || m_current.type == TT_PAR2) {
        // λ
    } else {
        showError();
    }
}

// <factor-a> ::= <factor> | “!” <facotr>
void SyntaticAnalysis::procFactor_a() {
    //std::cout << "ENTROU EM <factor-a>" << std::endl;
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
    //std::cout << "ENTROU EM <factor>" << std::endl;
    if(m_current.type == TT_ID) {
        eat(TT_ID);
    } else if(m_current.type == TT_INTEGER || m_current.type == TT_LITERAL || m_current.type == TT_REAL) {
        procConstant();
    } else if(m_current.type == TT_PAR1) {
        eat(TT_PAR1);
        procExpression();
        eat(TT_PAR2);
    }
}

// <relop> ::= “>” | “>=” | “<” | “<=”  | “!=” | “==”
void SyntaticAnalysis::procRelop() {
    //std::cout << "ENTROU EM <relop>" << std::endl;
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
    //std::cout << "ENTROU EM <addop>" << std::endl;
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
    //std::cout << "ENTROU EM <mulop>" << std::endl;
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
    //std::cout << "ENTROU EM <constant>" << std::endl;
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

