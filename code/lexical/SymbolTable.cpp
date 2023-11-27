#include <map>
#include <iostream>
#include <string.h>
#include <iomanip>
#include "SymbolTable.h"

SymbolTable::SymbolTable() {

	m_symbols[";"] = new TableInfo(TT_SEMICOLON, "NULL");	  
	m_symbols[","] = new TableInfo(TT_COMMA, "NULL");       
	m_symbols["."] = new TableInfo(TT_PERIOD, "NULL");	  
	m_symbols[":"] = new TableInfo(TT_POINTS, "NULL");      
	m_symbols["("] = new TableInfo(TT_PAR1, "NULL");         
	m_symbols[")"] = new TableInfo(TT_PAR2, "NULL");        
    m_symbols["{"] = new TableInfo(TT_CHAV1, "NULL");        
    m_symbols["}"] = new TableInfo(TT_CHAV2, "NULL");     
	//m_symbols["\""] = TT_QUOTE, "NULL"); 
	m_symbols["=="] = new TableInfo(TT_EQUAL, "NULL"); 
	m_symbols["="] = new TableInfo(TT_ASSIGN, "NULL"); 
	m_symbols["!="] = new TableInfo(TT_NOT_EQUAL, "NULL");  
	m_symbols["<"] = new TableInfo(TT_LOWER, "NULL");     
	m_symbols[">"] = new TableInfo(TT_GREATER, "NULL");      
	m_symbols["<="] = new TableInfo(TT_LESS_EQUAL, "NULL");
	m_symbols[">="] = new TableInfo(TT_GREATER_EQUAL, "NULL");
	m_symbols["&&"] = new TableInfo(TT_AND, "NULL");       
	m_symbols["||"] = new TableInfo(TT_OR, "NULL");          
    m_symbols["!"] = new TableInfo(TT_NOT, "NULL");      
	m_symbols["+"] = new TableInfo(TT_ADD, "NULL");   
	m_symbols["-"] = new TableInfo(TT_SUB, "NULL");      
	m_symbols["*"] = new TableInfo(TT_MUL, "NULL");         
	m_symbols["/"] = new TableInfo(TT_DIV, "NULL");       
	m_symbols["class"] = new TableInfo(TT_CLASS, "NULL");	  
	m_symbols["if"] = new TableInfo(TT_IF, "NULL");        
	m_symbols["else"] = new TableInfo(TT_ELSE, "NULL");         
	m_symbols["while"] = new TableInfo(TT_WHILE, "NULL");
    m_symbols["write"] = new TableInfo(TT_WRITE, "NULL");                 
	m_symbols["read"] = new TableInfo(TT_READ, "NULL");        
	m_symbols["do"] = new TableInfo(TT_DO, "NULL");
	m_symbols["int"] = new TableInfo(TT_INT, "NULL");
	m_symbols["float"] = new TableInfo(TT_FLOAT, "NULL");
	m_symbols["string"] = new TableInfo(TT_STRING, "NULL");



}
SymbolTable::~SymbolTable(){

}

bool SymbolTable::contains(const std::string& token) const {
    return m_symbols.find(token) != m_symbols.end();

}

enum TokenType SymbolTable::find(const std::string& token) {
	if(this->contains(token)) {
		return m_symbols[token]->token;
	} else {
		m_symbols[token]->token = TT_ID;  // Adiciona identificador na tabela de símbolos
		return TT_ID;
	}
}

void SymbolTable::showTable() const {
	
	for (auto it = m_symbols.begin(); it != m_symbols.end(); it++) {
		std::cout << std::setw(15) << it->first;
		std::cout << std::setw(2) << " ";  
		std::cout << "|";
		std::cout << std::setw(2) << " ";
		std::cout << std::setw(4) << it->second << std::endl;
	}
}

void SymbolTable::addId(const std::string& token) {

}