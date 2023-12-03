#ifndef EXPRESSION_L_H
#define EXPRESSION_L_H

class RelopExpr;
class ExprType;

class Expression_L {
	public:
		

		Expression_L(int line);
		virtual ~Expression_L();

        int m_line;
		ExprType* m_type;
		RelopExpr* m_op;

};

#endif