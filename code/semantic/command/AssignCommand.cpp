#include "AssignCommand.h"
#include <iostream>
#include <iomanip>

#include "../../semantic/declaration/Identifier.h"
#include "../type/ExprType.h"


AssignCommand::AssignCommand(int line)
    :Command(line) { 

}

AssignCommand::~AssignCommand() {
    delete m_type;
}

ExprType* AssignCommand::rule(Identifier* tb) {

  
}       
