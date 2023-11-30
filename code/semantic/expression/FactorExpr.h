#ifndef FACTOR_EXPR_H
#define FACTOR_EXPR_H

class ExprType;
class TableInfo;

class FactorExpr {
    public:
        FactorExpr(int line);
        virtual ~FactorExpr();

        ExprType* expr(TableInfo* tb);

        int m_line;
        ExprType* m_type;

};

#endif