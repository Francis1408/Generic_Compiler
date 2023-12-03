#include "Simple_Expr_l.h"
#include "../type/ExprType.h"
#include "Term.h"
#include "AddopExpr.h"
#include <iostream>
#include <iomanip>


Simple_Expr_L::Simple_Expr_L(int line)  { 
    this->m_line = line;

}

Simple_Expr_L::~Simple_Expr_L() {

}

ExprType* Simple_Expr_L::expr(Term_Expr* tm, Simple_Expr_L* sel) {

    if(sel->m_type->type == "NULL") {
        return new ExprType(tm->m_type->type, this->m_line);
    } else if(sel->m_type->type  != tm->m_type->type){
        std::cout << "Erro na linha: ";
        std::cout << std::setw(2) << std::setfill('0') << this->m_line << std::endl;
        std::cout << "Operacao de tipo "<< sel->m_type->type << " e " << tm->m_type->type << " nao compativeis" <<std::endl;
        exit(1);
        return new ExprType("ERROR", this->m_line);

    } else {  
        if(sel->m_type->type == "BOOL" && sel->m_op->m_op != AddopExpr::OR) {
            std::cout << "Erro na linha: ";
            std::cout << std::setw(2) << std::setfill('0') << this->m_line << std::endl;
            std::cout << "Operacao aritimetica nao suporta tipo logico" <<std::endl;
            exit(1);
            return new ExprType("ERROR", this->m_line);
        }
        return new ExprType(tm->m_type->type, this->m_line);
    }
}


