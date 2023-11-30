#include "FactorExpr.h"
#include <iostream>
#include <iomanip>

#include "../../lexical/TableInfo.h"
#include "../type/ExprType.h"

FactorExpr::FactorExpr(int line) { 
    this->m_line = line;
}

FactorExpr::~FactorExpr() {
    delete m_type;
}
     
ExprType* FactorExpr::expr(TableInfo* tb) {

    if(tb->type == "ERROR") {
        std::cout << "Erro na linha: ";
        std::cout << std::setw(2) << std::setfill('0') << this->m_line << std::endl;
        std::cout << "Identificador [" << tb->token << "] nao declarado"<< std::endl;

        exit(1);
    } else {
        return new ExprType(tb->type,this->m_line);
        
    }
    
} 