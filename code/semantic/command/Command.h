#ifndef COMMAND_H
#define COMMAND_H

class ExprType;

class Command {
    public:
        virtual ~Command() {}

        int line() const { return m_line; }

        int m_line;
        ExprType* m_type;
        
    protected:
        Command(int line) : m_line(line) {}

        
};

#endif