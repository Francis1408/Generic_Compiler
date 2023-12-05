#include "AssignCommand.h"
#include <iostream>
#include <iomanip>

#include "../type/ExprType.h"
#include "../expression/Simple_Expr.h"
#include "../../lexical/TableInfo.h"


AssignCommand::AssignCommand(int line)
    :Command(line) { 

}

AssignCommand::~AssignCommand() {
    delete m_type;
}

ExprType* AssignCommand::rule(Simple_Expr* se, TableInfo* tb, std::string id) {
    if(se->m_type->type == tb->type) {
        return new ExprType("NULL", this->m_line);

    } else {
        std::cout << "Erro na linha: ";
        std::cout << std::setw(2) << std::setfill('0') << this->m_line << std::endl;
        std::cout << "Indentificador " << id << " do tipo " << tb->type 
                  <<" nao suporta expressao do tipo " << se->m_type->type << std::endl;
        exit(1);
            return new ExprType("ERROR", this->m_line);
        }

}       
