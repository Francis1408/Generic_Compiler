#ifndef WRITE_COMMAND_H
#define WRITE_COMMAND_H

#include "Command.h"

class WriteCommand : public Command {
    public:
        WriteCommand(int line);
        virtual ~WriteCommand();

        virtual void rule();
    private:
};

#endif