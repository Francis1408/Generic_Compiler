#ifndef TERM_L_EXPR_H
#define TERM_L_EXPR_H

class MulopExpr;
class ExprType;
class FactorExpr;

class Term_L_Expr {
	public:
		

		Term_L_Expr(int line);
		virtual ~Term_L_Expr();
		ExprType* expr( FactorExpr* fe, Term_L_Expr* tl);

        int m_line;
		ExprType* m_type;
		MulopExpr* m_op;

};

#endif