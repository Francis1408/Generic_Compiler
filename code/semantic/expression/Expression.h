#ifndef EXPRESSION_H
#define EXPRESSION_H

class ExprType;
class Simple_Expr;
class Expression_L;

class Expression {
	public:
		

		Expression(int line);
		virtual ~Expression();
        ExprType* expr(Expression_L* exl, Simple_Expr* se);

        int m_line;
		ExprType* m_type;


};

#endif