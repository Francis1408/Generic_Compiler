#ifndef SIMPLE_L_EXPR_H
#define SIMPLE_L_EXPR_H

class AddopExpr;
class ExprType;
class Term_Expr;

class Simple_Expr_L {
	public:
		

		Simple_Expr_L(int line);
		virtual ~Simple_Expr_L();
		ExprType* expr(Term_Expr* tm, Simple_Expr_L* sel);

        int m_line;
		ExprType* m_type;
		AddopExpr* m_op;

};

#endif