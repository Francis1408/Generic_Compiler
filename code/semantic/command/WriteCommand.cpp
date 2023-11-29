#include "WriteCommand.h"

WriteCommand::WriteCommand(int line, ExprType* type)
    :Command(line), m_type(type) { 

}

WriteCommand::~WriteCommand() {
    delete m_type;
}

bool WriteCommand::rule(ExprType* type) {

}       
