#include "StatementList.h"
#include "Statement.h"
#include "../type/ExprType.h"
#include <iostream>
#include <iomanip>

StatementList::StatementList(int m_line) {
    this->m_line = m_line;
}

StatementList::~StatementList(){

}

void StatementList::addStmt(Statement* stmt) {
    this->stmtList.push_back(stmt);
}

void StatementList::showList() {
    int counter = 1;
    for(std::list<Statement*>::iterator it = this->stmtList.begin(),
        ed = this->stmtList.end(); it != ed; it++, counter++) {
            Statement* i = *it;
            std::cout << "Statement(" << counter << "): "<< i->m_type->type << std::endl;
        }
}

ExprType* StatementList::getType() {
    for(std::list<Statement*>::iterator it = this->stmtList.begin(),
        ed = this->stmtList.end(); it != ed; it++) {
            Statement* i = *it;
            if(i->m_type->type != "NULL") {
                std::cout << "Erro na linha: ";
                std::cout << std::setw(2) << std::setfill('0') << i->m_line << std::endl;
                std::cout << "Statement nao retornou tipo vazio"<< std::endl;
                exit(1);
            }
            
        }
    return new ExprType("NULL", this->m_line);
}



