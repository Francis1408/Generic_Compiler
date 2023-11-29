#ifndef READ_COMMAND_H
#define READ_COMMAND_H

#include "Command.h"

class ExprType;
class TableInfo;

class ReadCommand : public Command {
    public:
        ReadCommand(int line);
        virtual ~ReadCommand();

        ExprType* rule(TableInfo* tb);
};

#endif