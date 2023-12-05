#ifndef STATEMENT_H
#define STATEMENT_H


class ExprType;

class Statement {
    public:
        Statement(int m_line);
        virtual ~Statement();

        ExprType* m_type;
        int m_line;



};

#endif