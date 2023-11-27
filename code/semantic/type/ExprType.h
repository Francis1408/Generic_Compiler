#ifndef EXPR_TYPE_H
#define EXPR_TYPE_H

#include <string>

class ExprType {
    public:
        ExprType(std::string type, int m_line);
        virtual ~ExprType();

        int m_line;
        std::string type;

};

#endif