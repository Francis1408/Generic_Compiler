#ifndef ADDOP_EXPR_H
#define ADDOP_EXPR_H

class AddopExpr {
	public:
		enum Op {
		    ADD,    // *
	        SUB,    // /
	        OR,    // &&
		};

		AddopExpr(int line, enum Op op);
		virtual ~AddopExpr();

        enum Op m_op;
        int m_line;

};

#endif