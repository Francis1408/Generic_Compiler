CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=compiler 
OBJS=compiler.o  lexical/TableInfo.o lexical/SymbolTable.o lexical/LexicalAnalysis.o \
	 syntatic/SyntaticAnalysis.o \
	 semantic/type/ExprType.o \
	 semantic/declaration/IdentList.o \
	 semantic/declaration/Identifier.o \
	 semantic/command/ReadCommand.o \
	 semantic/command/DoSuffixCommand.o \
	 semantic/command/DoCommand.o \
	 semantic/command/IfCommand.o \
	 semantic/command/AssignCommand.o \
	 semantic/command/WriteCommand.o \
	 semantic/command/Statement.o \
	 semantic/command/StatementList.o \
	 semantic/expression/AddopExpr.o \
	 semantic/expression/MulopExpr.o  \
	 semantic/expression/RelopExpr.o \
	 semantic/expression/FactorExpr.o \
	 semantic/expression/Term_l.o \
	 semantic/expression/Term.o \
	 semantic/expression/Simple_Expr_l.o \
	 semantic/expression/Simple_Expr.o \
	 semantic/expression/Expression_l.o \
	 semantic/expression/Expression.o 

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	cp $(TARGET) /usr/local/bin

compiler.o:

lexical/TableInfo.o : lexical/TokenType.h

lexical/SymbolTable.o: lexical/TokenType.h lexical/TableInfo.h

lexical/LexicalAnalysis.o: lexical/Lexeme.h lexical/SymbolTable.h

syntatic/SyntaticAnalysis.o: syntatic/SyntaticAnalysis.h semantic/command/*.h semantic/type/*.h semantic/declaration/*.h

semantic/type/ExprType.o: semantic/type/ExprType.h 

semantic/declaration/IdentList.o: semantic/declaration/IdentList.h semantic/declaration/Identifier.h

semantic/declaration/Identifier.o: semantic/declaration/Identifier.h

semantic/command/AssignCommand.o: semantic/command/AssignCommand.h lexical/TableInfo.h semantic/expression/Simple_Expr.h semantic/type/ExprType.h 

semantic/command/ReadCommand.o: semantic/type/ExprType.h semantic/command/Command.h lexical/TableInfo.h

semantic/command/WriteCommand.o: semantic/command/WriteCommand.h semantic/command/Command.h semantic/type/ExprType.h

semantic/command/DoSuffixCommand.o: semantic/command/DoSuffixCommand.h semantic/command/Command.h semantic/type/ExprType.h

semantic/command/DoCommand.o: semantic/command/DoCommand.h semantic/command/Command.h

semantic/command/IfCommand.o: semantic/command/IfCommand.h semantic/expression/Expression.h semantic/command/StatementList.h

semantic/command/Statement.o: semantic/command/WriteCommand.h semantic/type/ExprType.h

semantic/command/StatementList.o: semantic/command/StatementList.h semantic/command/Statement.h semantic/type/ExprType.h

semantic/expression/FactorExpr.o: semantic/expression/FactorExpr.h semantic/type/ExprType.h lexical/TableInfo.h

semantic/expression/RelopExpr.o: semantic/expression/RelopExpr.h

semantic/expression/AddopExpr.o: semantic/expression/AddopExpr.h

semantic/expression/MulopExpr.o: semantic/expression/MulopExpr.h

semantic/expression/Term_l.o: semantic/expression/Term_l.h semantic/type/ExprType.h semantic/expression/MulopExpr.h semantic/expression/FactorExpr.h

semantic/expression/Term.o: semantic/expression/Term.h semantic/type/ExprType.h semantic/expression/MulopExpr.h semantic/expression/FactorExpr.h

semantic/expression/Simple_Expr_l.o: semantic/expression/Simple_Expr_l.h semantic/type/ExprType.h semantic/expression/AddopExpr.h semantic/expression/Term.h

semantic/expression/Simple_Expr.o: semantic/expression/Simple_Expr.h semantic/type/ExprType.h semantic/expression/AddopExpr.h semantic/expression/Term.h

semantic/expression/Expression_l.o: semantic/expression/Expression_l.h semantic/expression/RelopExpr.h semantic/type/ExprType.h

semantic/expression/Expression.o: semantic/expression/Expression.h semantic/expression/Expression_l.h semantic/expression/Simple_Expr.h semantic/type/ExprType.h



$(TARGET): $(OBJS)
		   $(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<