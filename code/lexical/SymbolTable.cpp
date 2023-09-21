#include <map>
#include <iostream>
#include <string.h>
#include "SymbolTable.h"

SymbolTable::SymbolTable() {

	m_symbols[";"] = TT_SEMICOLON;	  
	m_symbols[","] = TT_COMMA;       
	m_symbols["."] = TT_PERIOD;	  
	m_symbols[":"] = TT_POINTS;      
	m_symbols["("] = TT_PAR1;         
	m_symbols[")"] = TT_PAR2;        
    m_symbols["{"] = TT_CHAV1;        
    m_symbols["}"] = TT_CHAV2;     
	m_symbols["\""] = TT_QUOTE; 
	m_symbols["=="] = TT_EQUAL; 
	m_symbols["="] = TT_ASSIGN; 
	m_symbols["!="] = TT_NOT_EQUAL;  
	m_symbols["<"] = TT_LOWER;     
	m_symbols[">"] = TT_GREATER;      
	m_symbols["<="] = TT_LESS_EQUAL;
	m_symbols[">="] = TT_GREATER_EQUAL;
	m_symbols["&&"] = TT_AND;       
	m_symbols["||"] = TT_OR;          
    m_symbols["!"] = TT_NOT;      
	m_symbols["+"] = TT_ADD;   
	m_symbols["-"] = TT_SUB;      
	m_symbols["*"] = TT_MUL;         
	m_symbols["/"] = TT_DIV;       
	m_symbols["class"] = TT_CLASS;	  
	m_symbols["if"] = TT_IF;        
	m_symbols["else"] = TT_ELSE;         
	m_symbols["while"] = TT_WHILE;
    m_symbols["write"] = TT_WRITE;                 
	m_symbols["read"] = TT_READ;        
	m_symbols["do"] = TT_DO;
	m_symbols["int"] = TT_INT;
	m_symbols["float"] = TT_FLOAT;
	m_symbols["string"] = TT_STRING;


}
SymbolTable::~SymbolTable(){

}

bool SymbolTable::contains(const std::string& token) const {
    return m_symbols.find(token) != m_symbols.end();

}
enum TokenType SymbolTable::find(const std::string& token) {
	if(this->contains(token)) {
		return m_symbols[token];
	} else {
		m_symbols[token] = TT_ID; // Adiciona identificador na tabela de símbolos
		return TT_ID;
	}
}

void SymbolTable::showTable() const {
	
	for (auto it = m_symbols.begin(); it != m_symbols.end(); it++) {
		std::cout << it->first << " : " << it->second << std::endl;
	}
}