#include "Term_l.h"
#include "../type/ExprType.h"
#include "FactorExpr.h"
#include "MulopExpr.h"
#include <iostream>
#include <iomanip>


Term_L_Expr::Term_L_Expr(int line)  { 
    this->m_line = line;

}

Term_L_Expr::~Term_L_Expr() {

}

ExprType* Term_L_Expr::expr(FactorExpr* fe, Term_L_Expr* tl) {

    if(tl->m_type->type == "NULL") {
        return new ExprType(fe->m_type->type, this->m_line);
    } else if(tl->m_type->type  != fe->m_type->type){
        std::cout << "Erro na linha: ";
        std::cout << std::setw(2) << std::setfill('0') << this->m_line << std::endl;
        std::cout << "Operacao de tipo "<< tl->m_type->type << " e " << fe->m_type->type << " nao compativeis" <<std::endl;
        exit(1);
        return new ExprType("ERROR", this->m_line);
    
    } else if(tl->m_type->type == "STRING") {
        std::cout << "Erro na linha: ";
        std::cout << std::setw(2) << std::setfill('0') << this->m_line << std::endl;
        std::cout << "Operacao nao suporta tipo String " <<std::endl;
        exit(1);
        return new ExprType("ERROR", this->m_line);
    } 
    else {
        if (tl->m_type->type == "INTEGER" && tl->m_op->m_op == MulopExpr::DIV) {
            return new ExprType("FLOAT", this->m_line);
        }   
        else if(tl->m_type->type == "BOOL" && tl->m_op->m_op != MulopExpr::AND) {
            std::cout << "Erro na linha: ";
            std::cout << std::setw(2) << std::setfill('0') << this->m_line << std::endl;
            std::cout << "Operacao aritimetica nao suporta tipo logico" <<std::endl;
            exit(1);
            return new ExprType("ERROR", this->m_line);
        }
        return new ExprType(fe->m_type->type, this->m_line);
    }
}


