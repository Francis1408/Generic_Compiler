#ifndef ASSIGN_COMMAND_H
#define ASSIGN_COMMAND_H

#include "Command.h"
#include <string>

class ExprType;
class TableInfo;
class Simple_Expr;

class AssignCommand : public Command {
    public:
        AssignCommand(int line);
        virtual ~AssignCommand();

        ExprType* rule(Simple_Expr* se, TableInfo* tb, std::string id);
};

#endif