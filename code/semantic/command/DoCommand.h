#ifndef DO_COMMAND
#define DO_COMMAND

#include "Command.h"
#include <string>


class DoCommand : public Command {
    public:
        DoCommand(int line);
        virtual ~DoCommand();

};

#endif