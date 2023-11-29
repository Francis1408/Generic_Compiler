#ifndef WRITE_COMMAND_H
#define WRITE_COMMAND_H

#include "Command.h"

class ExprType;

class WriteCommand : public Command {
    public:
        WriteCommand(int line,  ExprType* type);
        virtual ~WriteCommand();

        virtual bool rule(ExprType* type);

        ExprType* m_type;
        
    private:
};

#endif