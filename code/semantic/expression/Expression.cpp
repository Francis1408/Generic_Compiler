#include "Expression.h"
#include "../type/ExprType.h"
#include "RelopExpr.h"
#include "Expression_l.h"
#include "Simple_Expr.h"
#include <iostream>
#include <iomanip>


Expression::Expression(int line)  { 
    this->m_line = line;

}

Expression::~Expression() {

}

ExprType* Expression::expr(Expression_L* exl, Simple_Expr* se) {

    if(exl->m_type->type == "NULL") {
        return new ExprType(se->m_type->type, this->m_line);
    } else if(exl->m_type->type  != se->m_type->type){
        std::cout << "Erro na linha: ";
        std::cout << std::setw(2) << std::setfill('0') << this->m_line << std::endl;
        std::cout << "Operacao de tipo "<< exl->m_type->type << " e " << se->m_type->type << " nao compativeis" <<std::endl;
        exit(1);
        return new ExprType("ERROR", this->m_line);

    } else {
        return new ExprType("BOOL", this->m_line);
    }
}




