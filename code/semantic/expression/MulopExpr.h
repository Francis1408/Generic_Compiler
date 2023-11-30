#ifndef MULOP_EXPR_H
#define MULOP_EXPR_H

class MulopExpr {
	public:
		enum Op {
		    MUL,    // *
	        DIV,    // /
	        AND,    // &&
		};

		MulopExpr(int line, enum Op op);
		virtual ~MulopExpr();

        enum Op m_op;
        int m_line;

};

#endif