#ifndef WRITE_COMMAND_H
#define WRITE_COMMAND_H

#include "Command.h"

class ExprType;
class Simple_Expr;

class WriteCommand : public Command {
    public:
        WriteCommand(int line);
        virtual ~WriteCommand();

        ExprType* rule(Simple_Expr* se); 

        ExprType* m_type;
        
};

#endif