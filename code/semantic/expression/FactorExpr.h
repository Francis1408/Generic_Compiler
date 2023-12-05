#ifndef FACTOR_EXPR_H
#define FACTOR_EXPR_H

class ExprType;
class TableInfo;

#include <string>

class FactorExpr {
    public:
        FactorExpr(int line);
        virtual ~FactorExpr();

        ExprType* expr(TableInfo* tb, std::string id);

        int m_line;
        ExprType* m_type;

};

#endif