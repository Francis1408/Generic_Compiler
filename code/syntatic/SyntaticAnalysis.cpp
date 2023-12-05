#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "../semantic/type/ExprType.h"
#include "../semantic/command/ReadCommand.h"
#include "../semantic/command/WriteCommand.h"
#include "../semantic/command/AssignCommand.h"
#include "../semantic/command/IfCommand.h"
#include "../semantic/command/DoSuffixCommand.h"
#include "../semantic/command/DoCommand.h"
#include "../semantic/command/StatementList.h"
#include "../semantic/command/Statement.h"
#include "../semantic/declaration/IdentList.h"
#include "../semantic/declaration/Identifier.h"
#include "../semantic/expression/RelopExpr.h"
#include "../semantic/expression/MulopExpr.h"
#include "../semantic/expression/AddopExpr.h"
#include "../semantic/expression/FactorExpr.h"
#include "../semantic/expression/Term_l.h"
#include "../semantic/expression/Term.h"
#include "../semantic/expression/Simple_Expr_l.h"
#include "../semantic/expression/Simple_Expr.h"
#include "../semantic/expression/Expression_l.h"
#include "../semantic/expression/Expression.h"

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
    /*std::cout << "Expected (..., " << tt2str(type) 
              << "), found (\"" << m_current.token << "\", " 
              << tt2str(m_current.type) << ")" << std::endl ;
    */
    
    if(type ==  m_current.type && type != TT_END_OF_FILE) {
        advance();
    } else if (type == TT_END_OF_FILE) {
        std::cout << "Análise sintática feita com sucesso!" << std::endl;
        advance();
    } else {
        showError();
    }
}

void SyntaticAnalysis::showError() {
    std::cout << "Erro na linha: ";
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
    ExprType* eType =  procType();
    IdentList* iList = procIdent_list();

    //Verfica unicidade e adiciona ID's na tabela
    for(std::list<Identifier*>::iterator it = iList->idList.begin(),
        ed = iList->idList.end(); it != ed; it++) {
            Identifier* i = *it;
            try{
                if(m_lex.addToken(i->id, eType->type));
                else {
                    throw(m_lex.line());
                }
                //std::cout << "Identifier(" << i->id << "): ADICIONADO "<< std::endl;
            }
            catch(int line) {
                std::cout << "Erro na linha: ";
                std::cout << std::setw(2) << std::setfill('0') << line << std::endl;
                std::cout << "Identificador [" << i->id << "] ja declarado"<< std::endl;

                exit(1);
            }
        }

}

// <ident-list> ::= identifier {“,” identifier}
IdentList* SyntaticAnalysis::procIdent_list() {
    //std::cout << "ENTROU EM <ident-list>" << std::endl;
    std::string tmp = m_current.token;
    eat(TT_ID);

    int line = m_lex.line();
    IdentList* identifierList = new IdentList(line);
    Identifier* id = new Identifier(tmp, line);
    identifierList->addId(id);
    
    while(m_current.type == TT_COMMA) {
        eat(TT_COMMA);
        tmp = m_current.token;
        eat(TT_ID);
        line = m_lex.line();
        Identifier* id = new Identifier(tmp, line);
        identifierList->addId(id);
    }
    //identifierList->showList();
    return identifierList;
}

// <type> ::= int | string | float
ExprType* SyntaticAnalysis::procType() {
    std::string type;
    int line;

    if(m_current.type == TT_INT) {
        type = "INTEGER";
        eat(TT_INT);
        line = m_lex.line();

    } else if(m_current.type == TT_STRING) {
        type = "STRING";
        eat(TT_STRING);
        line = m_lex.line();

    } else if(m_current.type == TT_FLOAT) {
        type = "FLOAT";
        eat(TT_FLOAT);
        line = m_lex.line();
    } else {
        type = "ERROR";
        showError();
        line = m_lex.line();
    }

    ExprType* et = new ExprType(type, line);
 
    return et;

}

// <body> ::= “{” <stmt-list> “}”
void SyntaticAnalysis::procBody() {
    //std::cout << "ENTROU EM <body>" << std::endl; 
    eat(TT_CHAV1);
    procStmt_list();
    eat(TT_CHAV2);

}

// <stmt-list> ::=  <stmt> “;” {<stmt> “;”}
StatementList* SyntaticAnalysis::procStmt_list() {
    //std::cout << "ENTROU EM <stmt-list>" << std::endl;
    int line = m_lex.line();
    Statement* stmt =  procStmt();
    StatementList* stmtList = new StatementList(line);
    stmtList->addStmt(stmt); 

    eat(TT_SEMICOLON);
    while(m_current.type == TT_ID || m_current.type == TT_IF || m_current.type == TT_DO || m_current.type == TT_READ || m_current.type == TT_WRITE) {
        Statement* stmt = procStmt();
        stmtList->addStmt(stmt);
        eat(TT_SEMICOLON);
    }

    stmtList->m_type = stmtList->getType();
    return stmtList;

}

//<stmt> ::= <assign-stmt> | <if-stmt> | <do-stmt> | <read-stmt> | <write-stmt>
Statement* SyntaticAnalysis::procStmt() {
    //std::cout << "ENTROU EM <stmt>" << std::endl;
    if(m_current.type == TT_ID) {
        int line = m_lex.line();
        AssignCommand* asc = procAssign_stmt();
        Statement* stmt = new Statement(line);
        stmt->m_type = asc->m_type;
        return stmt;

    } else if(m_current.type == TT_IF) {
        int line = m_lex.line();
        IfCommand* ifc = procIf_stmt();
        Statement* stmt = new Statement(line);
        stmt->m_type = ifc->m_type;
        return stmt;

    } else if (m_current.type == TT_DO) {
        int line = m_lex.line();
        DoCommand* dc = procDo_stmt();
        Statement* stmt = new Statement(line);
        stmt->m_type = dc->m_type;
        return stmt;

    } else if (m_current.type == TT_READ) {
        int line = m_lex.line();
        ReadCommand* rc = procRead_stmt();
        Statement* stmt = new Statement(line);
        stmt->m_type = rc->m_type;
        return stmt;

    } else if (m_current.type == TT_WRITE) {
        int line = m_lex.line();
        WriteCommand* wc =  procWrite_stmt();
        Statement* stmt = new Statement(line);
        stmt->m_type = wc->m_type;
        return stmt;

    } else {
        showError();
        return new Statement(m_lex.line());
    }

}

// <assign-stmt> ::= identifier “=” <simple_expr>
AssignCommand* SyntaticAnalysis::procAssign_stmt() {
    //std::cout << "ENTROU EM <assign-stmt>" << std::endl;

    std::string tmp = m_current.token;
    eat(TT_ID);
    int line = m_lex.line();
    AssignCommand* ac = new AssignCommand(line);
    TableInfo* tb = m_lex.findToken(tmp);
    eat(TT_ASSIGN);
    Simple_Expr* se = procSimple_expr();
    ac->m_type = ac->rule(se, tb, tmp);

    return ac;
}

// <if-stmt> ::= if “(” <condition> “)” “{” <stmt-list> “}” <if-stmt’>
IfCommand* SyntaticAnalysis::procIf_stmt() {
    //std::cout << "ENTROU EM <if-stmt>" << std::endl;
    eat(TT_IF);
    eat(TT_PAR1);
    Expression* ex = procCondition();
    eat(TT_PAR2);
    eat(TT_CHAV1);
    StatementList* stmtList =  procStmt_list();
    eat(TT_CHAV2);
    IfCommand* ifcmdL = procIf_stmt_l();

    int line = m_lex.line();
    IfCommand* ifcmd = new IfCommand(line);
    ifcmd->m_type = ifcmd->rule(ex, stmtList);

    return ifcmd;

}

// <if-stmt’> ::= λ | else “{” <stmt-list> “}”
IfCommand* SyntaticAnalysis::procIf_stmt_l() {
    //std::cout << "ENTROU EM <if-stmt'>" << std::endl;
    if(m_current.type == TT_ELSE) {
        int line = m_lex.line();
        IfCommand* ifcmd = new IfCommand(line);
        advance();
        eat(TT_CHAV1);
        StatementList* stmtList = procStmt_list();
        eat(TT_CHAV2);

        ifcmd->m_type = stmtList->m_type;
        return ifcmd;
    } else if(m_current.type == TT_SEMICOLON ) {
        // λ
        int line = m_lex.line();
        IfCommand* ifcmd = new IfCommand(line);
        ifcmd->m_type = new ExprType("NULL", line);
        return ifcmd;

    } else {
        showError();
        return new IfCommand(m_lex.line());
    }
} 

// <condition> ::= <expression>
Expression* SyntaticAnalysis::procCondition() {
    //std::cout << "ENTROU EM <condition>" << std::endl;
    return procExpression();
}

// <do-stmt> ::= do “{” <stmt-list> “}” <do-suffix>
DoCommand* SyntaticAnalysis::procDo_stmt() {
    //std::cout << "ENTROU EM <do-stmt>" << std::endl;
    int line = m_lex.line();
    DoCommand* dc = new DoCommand(line);
    eat(TT_DO);
    eat(TT_CHAV1);
    StatementList* stmtList =  procStmt_list();
    eat(TT_CHAV2);
    DoSuffixCommand* dsc = procDo_suffix();
    
    dc->m_type = stmtList->m_type;
    return dc;
}

// <do-suffix> ::= while “(” <condition> “)”
DoSuffixCommand* SyntaticAnalysis::procDo_suffix() {
    //std::cout << "ENTROU EM <do-suffix>" << std::endl;
    eat(TT_WHILE);
    eat(TT_PAR1);
    Expression* exp =  procCondition();
    int line = m_lex.line();
    eat(TT_PAR2);

    DoSuffixCommand* dsc = new DoSuffixCommand(line);
    dsc->m_type = dsc->rule(exp);

    return dsc;
}

// <read-stmt> ::= read “(” identifier “)”
ReadCommand* SyntaticAnalysis::procRead_stmt() {
    //std::cout << "ENTROU EM <read-stmt>" << std::endl;
    eat(TT_READ);
    eat(TT_PAR1);

    // Fetching identifier data
    std::string tmp = m_current.token;
    eat(TT_ID);
    int line = m_lex.line();
    ReadCommand* rc = new ReadCommand(line);
    TableInfo* tb = m_lex.findToken(tmp);
    eat(TT_PAR2);

    rc->m_type = rc->rule(tb, tmp);

    return rc;

}

// <write-stmt> ::= write “(” <writable> “)”
WriteCommand* SyntaticAnalysis::procWrite_stmt() {
    //std::cout << "ENTROU EM <write-stmt>" << std::endl;
    int line;

    eat(TT_WRITE);
    eat(TT_PAR1);
    Simple_Expr* se = procWritable();
    eat(TT_PAR2);
    line = m_lex.line();
    WriteCommand* wc = new WriteCommand(line);
    wc->m_type = wc->rule(se);

    return wc;
}

// <writable> ::= <simple-expr>
Simple_Expr* SyntaticAnalysis::procWritable() {
    //std::cout << "ENTROU EM <writable>" << std::endl;
    return procSimple_expr();
}

// <expression>	::= <simple-expr> <expression’>
Expression* SyntaticAnalysis::procExpression() {
    //std::cout << "ENTROU EM <expression>" << std::endl;
    int line;

    Simple_Expr* se =  procSimple_expr();
    Expression_L* exl = procExpression_l();
    
    line = m_lex.line();
    Expression* exp = new Expression(line);
    exp->m_type = exp->expr(exl, se);

    return exp;
    
}

// <expression’>	::= λ | <relop> <simple-expr>
Expression_L* SyntaticAnalysis::procExpression_l() {
    //std::cout << "ENTROU EM <expression'>" << std::endl;
    int line;

    if(m_current.type == TT_NOT_EQUAL || m_current.type == TT_GREATER || 
        m_current.type == TT_GREATER_EQUAL || m_current.type == TT_LOWER || m_current.type == TT_LESS_EQUAL || 
        m_current.type == TT_EQUAL) {
        RelopExpr* re = procRelop();
        Simple_Expr* se = procSimple_expr();
        line = m_lex.line();
        Expression_L* exl = new Expression_L(line);
        exl->m_op = re;
        exl->m_type = se->m_type;

        return exl;

    }
    else if(m_current.type == TT_PAR2) {
        // λ
        Expression_L* exl = new Expression_L(m_lex.line());
        exl->m_type = new ExprType("NULL",m_lex.line()); 

        return exl;

    } else {
        showError();
        return new Expression_L(m_lex.line());
    }
}


// <simple-expr> ::= <term> <simple-expr’>
Simple_Expr* SyntaticAnalysis::procSimple_expr() {
    int line;

    Term_Expr* tm = procTerm();
    Simple_Expr_L* sel = procSimple_expr_l();
    line = m_lex.line();
    Simple_Expr* se = new Simple_Expr(line);
    se->m_type = se->expr(tm, sel);

    return se;

}

// <simple-expr’> ::= <addop> <term> <simple-expr’> | λ
Simple_Expr_L* SyntaticAnalysis::procSimple_expr_l() {
    //std::cout << "ENTROU EM <simple-expr'>" << std::endl;
    int line;

    if(m_current.type ==  TT_ADD || m_current.type == TT_SUB || m_current.type == TT_OR) {
        AddopExpr* ae = procAddop();
        Term_Expr* tm =  procTerm();
        Simple_Expr_L* sel1 = procSimple_expr_l();

        line = m_lex.line();
        Simple_Expr_L* sel2 = new Simple_Expr_L(line);
        sel2->m_op = ae;
        sel2->m_type = sel2->expr(tm, sel1);

        return sel2;

    } else if(m_current.type == TT_PAR2 || m_current.type == TT_SEMICOLON || m_current.type == TT_NOT_EQUAL || m_current.type == TT_GREATER || 
       m_current.type == TT_GREATER_EQUAL || m_current.type == TT_LOWER || m_current.type == TT_LESS_EQUAL || 
       m_current.type == TT_EQUAL) {
        // λ

       Simple_Expr_L* sel = new Simple_Expr_L(m_lex.line());
       sel->m_type = new ExprType("NULL",m_lex.line());

       return sel;
    } else {
        showError();
        return new Simple_Expr_L(m_lex.line());
    }
}

// <term>  ::= <factor-a> <term’>
Term_Expr* SyntaticAnalysis::procTerm() {
    int line;

    FactorExpr* fe =  procFactor_a();
    Term_L_Expr* te =  procTerm_l();
    line = m_lex.line();
    Term_Expr* tm = new Term_Expr(line);
    tm->m_type = tm->expr(fe, te);

    return tm;
}

// <term’> ::= <mulop> <factor-a> <term’> | λ
Term_L_Expr* SyntaticAnalysis::procTerm_l() {
    //std::cout << "ENTROU EM <term'>" << std::endl;
    int line;

    if(m_current.type ==  TT_MUL || m_current.type == TT_DIV || m_current.type == TT_AND) {
        MulopExpr* me =  procMulop();
        FactorExpr* fe =  procFactor_a();
        Term_L_Expr* tl1 = procTerm_l();

        line = m_lex.line();
        Term_L_Expr* tl2 = new Term_L_Expr(line);
        tl2->m_op = me;
        tl2->m_type = tl2->expr(fe, tl1);

        return tl2;


    } else if(m_current.type == TT_ADD || m_current.type == TT_SUB || m_current.type == TT_OR || 
              m_current.type == TT_SEMICOLON || m_current.type == TT_PAR2 || m_current.type == TT_NOT_EQUAL || m_current.type == TT_GREATER || 
              m_current.type == TT_GREATER_EQUAL || m_current.type == TT_LOWER || m_current.type == TT_LESS_EQUAL || 
              m_current.type == TT_EQUAL) {
        // λ
       Term_L_Expr* tl = new Term_L_Expr(m_lex.line());
       line = m_lex.line();
       tl->m_type = new ExprType("NULL",line);

       return tl;
    } else {
        showError();
        return new Term_L_Expr(m_lex.line());
    }
}

// <factor-a> ::= <factor> | “!” <facotr> | “-” <factor>
FactorExpr* SyntaticAnalysis::procFactor_a() {
    //std::cout << "ENTROU EM <factor-a>" << std::endl;
    if(m_current.type == TT_ID || m_current.type == TT_INTEGER || m_current.type == TT_LITERAL || m_current.type == TT_REAL || m_current.type == TT_PAR1) {
        FactorExpr* fe =  procFactor();
        return fe;

    } else if(m_current.type == TT_NOT) {
        eat(TT_NOT);
        FactorExpr* fe =  procFactor();  //precisa ser BOOL

        if(fe->m_type->type == "BOOL") {
            return fe;
        } else {
            std::cout << "Erro na linha: ";
            std::cout << std::setw(2) << std::setfill('0') << fe->m_line << std::endl;
            std::cout << "Expressao requer tipo logico"<< std::endl;
            exit(1);
        }

    } else if (m_current.type == TT_SUB) {
        eat(TT_SUB);
        FactorExpr* fe =  procFactor(); //precisa ser numerico

        if(fe->m_type->type == "INTEGER" || fe->m_type->type == "FLOAT") {
            return fe;
        } else {
            std::cout << "Erro na linha: ";
            std::cout << std::setw(2) << std::setfill('0') << fe->m_line << std::endl;
            std::cout << "Expressao requer tipo numerico"<< std::endl;
            exit(1);
        }
    } else {
        showError();
        return new FactorExpr(m_lex.line());
    }
}

// <factor>	::= identifier | <constant> | “(” <expression> “)”
FactorExpr* SyntaticAnalysis::procFactor() {
    //std::cout << "ENTROU EM <factor>" << std::endl;
    int line;

    if(m_current.type == TT_ID) {
        // Fetching identifier data
        std::string tmp = m_current.token;
        eat(TT_ID);
        int line = m_lex.line();

        FactorExpr* fe = new FactorExpr(line);
        TableInfo* tb = m_lex.findToken(tmp);

        fe->m_type = fe->expr(tb,tmp);

        return fe;

    } else if(m_current.type == TT_INTEGER || m_current.type == TT_LITERAL || m_current.type == TT_REAL) {
        ExprType* et =  procConstant();
        line = m_lex.line();
        FactorExpr* fe = new FactorExpr(line);
        fe->m_type = new ExprType(et->type, line);

        return fe;

    } else if(m_current.type == TT_PAR1) {
        eat(TT_PAR1);
        Expression* exp = procExpression();
        eat(TT_PAR2);

        line = m_lex.line();
        FactorExpr* fe = new FactorExpr(line);
        fe->m_type = exp->m_type;

        return fe;
        
    } else {
        showError();
        return new FactorExpr(m_lex.line());
    }
}

// <relop> ::= “>” | “>=” | “<” | “<=”  | “!=” | “==”
RelopExpr* SyntaticAnalysis::procRelop() {
    //std::cout << "ENTROU EM <relop>" << std::endl;
    int line;
    
    if(m_current.type == TT_EQUAL) {
        eat(TT_EQUAL);
        line = m_lex.line();
        RelopExpr* re = new RelopExpr(line, RelopExpr::EQUAL);
        return re;

    } else if ( m_current.type == TT_NOT_EQUAL) {
        eat(TT_NOT_EQUAL);
        line = m_lex.line();
        RelopExpr* re = new RelopExpr(line, RelopExpr::NOT_EQUAL);
        return re;

    } else if (m_current.type == TT_LOWER) {
        eat(TT_LOWER);
        line = m_lex.line();
        RelopExpr* re = new RelopExpr(line, RelopExpr::LOWER);
        return re;

    } else if (m_current.type == TT_GREATER) {
        eat(TT_GREATER);
        line = m_lex.line();
        RelopExpr* re = new RelopExpr(line, RelopExpr::GREATER);
        return re;

    } else if (m_current.type == TT_LESS_EQUAL) {
        eat(TT_LESS_EQUAL);
        line = m_lex.line();
        RelopExpr* re = new RelopExpr(line, RelopExpr::LESS_EQUAL);
        return re;

    } else if ( m_current.type == TT_GREATER_EQUAL) {
        eat(TT_GREATER_EQUAL);
        line = m_lex.line();
        RelopExpr* re = new RelopExpr(line, RelopExpr::GREATER_EQUAL);
        return re;
    } else {
        showError();
        return new RelopExpr(line, RelopExpr::ERROR);
    }
    
}

// <addop> ::= “+” | “-” | “||”
AddopExpr* SyntaticAnalysis::procAddop() {
    //std::cout << "ENTROU EM <addop>" << std::endl;
    int line;

    if(m_current.type == TT_ADD){
        eat(TT_ADD);
        line = m_lex.line();
        AddopExpr* ae = new AddopExpr(line, AddopExpr::ADD);
        return ae;
    } else if (m_current.type == TT_SUB) {
        eat(TT_SUB);
        line = m_lex.line();
        AddopExpr* ae = new AddopExpr(line, AddopExpr::SUB);
        return ae;
    } else if (m_current.type == TT_OR ) {
        eat(TT_OR);
        line = m_lex.line();
        AddopExpr* ae = new AddopExpr(line, AddopExpr::OR);
        return ae;
    } else {
        showError();
        return new AddopExpr(m_lex.line(), AddopExpr::ERROR);
    }
}

// <mulop> ::= “*” | “/” | “&&”
MulopExpr* SyntaticAnalysis::procMulop() {
   //std::cout << "ENTROU EM <mulop>" << std::endl;
    int line;

    if(m_current.type == TT_MUL) {
        eat(TT_MUL);
        line = m_lex.line();
        MulopExpr* me = new MulopExpr(line, MulopExpr::MUL);
        return me;
    } else if (m_current.type == TT_DIV) {
        eat(TT_DIV);
        line = m_lex.line();
        MulopExpr* me = new MulopExpr(line, MulopExpr::DIV);
        return me;
    } else if (m_current.type == TT_AND ) {
        eat(TT_AND);
        line = m_lex.line();
        MulopExpr* me = new MulopExpr(line, MulopExpr::AND);
        return me;
    } else {
        showError();
        return new MulopExpr(m_lex.line(), MulopExpr::ERROR);
    }
}

// <constant> ::= integer_const | literal | real_const
ExprType* SyntaticAnalysis::procConstant() {
    //std::cout << "ENTROU EM <constant>" << std::endl;
    std::string type;
    int line;

    if(m_current.type == TT_INTEGER) {
        type = "INTEGER";
        eat(TT_INTEGER);
        line = m_lex.line();
    } else if (m_current.type == TT_LITERAL) {
        type = "STRING";
        eat(TT_LITERAL);
        line = m_lex.line();
    } else if (m_current.type == TT_REAL ) {
        type = "FLOAT";
        eat(TT_REAL);
        line = m_lex.line();
    } else {
        type = "ERROR";
        showError();
    }

    ExprType* et = new ExprType(type, line);
    return et;
}

