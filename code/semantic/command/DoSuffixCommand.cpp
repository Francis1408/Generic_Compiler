#include "DoSuffixCommand.h"
#include <iostream>
#include <iomanip>

#include "../type/ExprType.h"
#include "../expression/Expression.h"


DoSuffixCommand::DoSuffixCommand(int line)
    :Command(line) { 

}

DoSuffixCommand::~DoSuffixCommand() {
    delete m_type;
}

ExprType* DoSuffixCommand::rule(Expression* se) {
    if(se->m_type->type == "BOOL") {
        return new ExprType("NULL", this->m_line);

    } else {
        std::cout << "Erro na linha: ";
        std::cout << std::setw(2) << std::setfill('0') << this->m_line << std::endl;
        std::cout << "Condition nao e do tipo booleano"<< std::endl;
        exit(1);
            return new ExprType("ERROR", this->m_line);
        }

}       
