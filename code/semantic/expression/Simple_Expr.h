#ifndef SIMPLE_EXPR_H
#define SIMPLE_EXPR_H

class ExprType;
class Simple_Expr_L;
class Term_Expr;

class Simple_Expr {
	public:
		

		Simple_Expr(int line);
		virtual ~Simple_Expr();
		ExprType* expr(Term_Expr* te, Simple_Expr_L* sel);

        int m_line;
		ExprType* m_type;

};

#endif