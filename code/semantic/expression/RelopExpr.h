#ifndef RELOP_EXPR_H
#define RELOP_EXPR_H

class RelopExpr {
	public:
		enum Op {
		    EQUAL,		  // ==
	        NOT_EQUAL,     // !=
	        LOWER,         // <
	        GREATER,       // >
	        LESS_EQUAL,    // <=
	        GREATER_EQUAL, // >=
		};

		RelopExpr(int line, enum Op op);
		virtual ~RelopExpr();

		virtual bool expr();

        enum Op m_op;
        int m_line;

};

#endif