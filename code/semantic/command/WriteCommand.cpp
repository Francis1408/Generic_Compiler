#include "WriteCommand.h"
#include "../type/ExprType.h"
#include "../expression/Simple_Expr.h"

WriteCommand::WriteCommand(int line)
    :Command(line) { 

}

WriteCommand::~WriteCommand() {
    delete m_type;
}

ExprType* WriteCommand::rule(Simple_Expr* se) {
    if(se->m_type->type != "ERROR") {
        return new ExprType("NULL", this->m_line);
    }
    else {
        return new ExprType("ERROR", this->m_line);
    }
}