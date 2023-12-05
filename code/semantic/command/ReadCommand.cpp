#include "ReadCommand.h"
#include <iostream>
#include <iomanip>
#include <string>

#include "../../lexical/TableInfo.h"
#include "../type/ExprType.h"


ReadCommand::ReadCommand(int line)
    :Command(line) { 

}

ReadCommand::~ReadCommand() {
    delete m_type;
}

ExprType* ReadCommand::rule(TableInfo* tb, std::string id) {

    if(tb->type == "ERROR") {
        std::cout << "Erro na linha: ";
        std::cout << std::setw(2) << std::setfill('0') << this->m_line+1 << std::endl;
        std::cout << "Identificador [" << id << "] nao declarado"<< std::endl;

        exit(1);
    } else {
        return new ExprType("NULL",this->m_line);
        
    }
    
}       
