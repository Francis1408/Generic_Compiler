#ifndef TERM_EXPR_H
#define TERM_EXPR_H

class ExprType;
class Term_L_Expr;
class FactorExpr;

class Term_Expr {
	public:
		

		Term_Expr(int line);
		virtual ~Term_Expr();
		ExprType* expr(FactorExpr* fe, Term_L_Expr* tl);

        int m_line;
		ExprType* m_type;

};

#endif