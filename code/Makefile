CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=compiler 
OBJS=compiler.o  lexical/TableInfo.o lexical/SymbolTable.o lexical/LexicalAnalysis.o \
	 syntatic/SyntaticAnalysis.o \
	 semantic/type/ExprType.o \
	 semantic/declaration/IdentList.o \
	 semantic/declaration/Identifier.o
	 

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

$(TARGET): $(OBJS)
		   $(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<