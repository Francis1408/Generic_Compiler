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
			ERROR,
		};

		RelopExpr(int line, enum Op op);
		virtual ~RelopExpr();

        enum Op m_op;
        int m_line;

};

#endif