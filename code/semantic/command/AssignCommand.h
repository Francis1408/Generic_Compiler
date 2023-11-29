#ifndef ASSIGN_COMMAND_H
#define ASSIGN_COMMAND_H

#include "Command.h"

class ExprType;
class TableInfo;
class Identifier;

class AssignCommand : public Command {
    public:
        AssignCommand(int line);
        virtual ~AssignCommand();

        ExprType* rule(Identifier* id);
};

#endif