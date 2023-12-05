#ifndef IF_COMMAND_H
#define IF_COMMAND_H

#include "Command.h"

class ExprType;
class Expression;
class StatementList;

class IfCommand : public Command {
    public:
        IfCommand(int line);
        virtual ~IfCommand();

        ExprType* rule(Expression* ex, StatementList* stmtList);

};

#endif