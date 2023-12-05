#ifndef DO_SUFFIX_COMMAND
#define DO_SUFFIX_COMMAND

#include "Command.h"
#include <string>

class ExprType;
class Expression;

class DoSuffixCommand : public Command {
    public:
        DoSuffixCommand(int line);
        virtual ~DoSuffixCommand();

        ExprType* rule(Expression* exp);
};

#endif