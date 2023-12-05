#include "IfCommand.h"
#include <iostream>
#include <iomanip>

#include "../type/ExprType.h"
#include "../expression/Expression.h"
#include "StatementList.h"


IfCommand::IfCommand(int line)
    :Command(line) { 

}

IfCommand::~IfCommand() {
    delete m_type;
}

ExprType* IfCommand::rule(Expression* ex, StatementList* stmtList) {

    if(ex->m_type->type == "BOOL") {
        return new ExprType(stmtList->m_type->type, this->m_line);
    } else {
        std::cout << "Erro na linha: ";
        std::cout << std::setw(2) << std::setfill('0') << this->m_line << std::endl;
        std::cout << "Condition nao e do tipo booleano"<< std::endl;
        exit(1);

        return new ExprType("ERROR", this->m_line);
    }
    
}       
