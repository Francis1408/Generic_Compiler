#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <string>

enum TokenType {
	// Specials
	 TT_UNEXPECTED_EOF = -2,
	 TT_INVALID_TOKEN  = -1,
	 TT_END_OF_FILE    =  0,

	//Symbols
	 TT_SEMICOLON,	   // ;
	 TT_COMMA,         // ,
	 TT_PERIOD,		   // .
	 TT_ASSIGN,        // =
	 TT_POINTS,        // :
	 TT_PAR1,          // (
	 TT_PAR2,          // )
     TT_CHAV1,         // {
     TT_CHAV2,         // }
	 TT_QUOTE,		   // “

	//Logic Operators
	 TT_EQUAL,		  // ==
	 TT_NOT_EQUAL,     // !=
	 TT_LOWER,         // <
	 TT_GREATER,       // >
	 TT_LESS_EQUAL,    // <=
	 TT_GREATER_EQUAL, // >=

	// Conector Operators
	 TT_AND,           // &&
	 TT_OR,            // ||
     TT_NOT,           // !

	// Arithmetic operators
	 TT_ADD,           // +
	 TT_SUB,           // -
	 TT_MUL,           // *
	 TT_DIV,           // /

	//Keywords
	 TT_CLASS,		  // class
	 TT_IF,            // if
	 TT_ELSE,          // else
	 TT_WHILE,         // while
	 TT_WRITE,         // write
	 TT_READ,          // read
	 TT_DO,			  // do
	 TT_INT,           // int
	 TT_FLOAT,         // float
	 TT_STRING,        // string

	//Others
	 TT_ID,           // varible       
	 TT_INTEGER,	  // Integer
	 TT_REAL,		  // Real number
	 TT_LITERAL,	  // String
};

inline std::string tt2str(enum TokenType type){

    switch (type) {

        // Specials
	case TT_UNEXPECTED_EOF:
        return "UNEXPECTED_EOF";
	case TT_INVALID_TOKEN:
        return "INVALID_TOKEN";
	case TT_END_OF_FILE:
        return "END_OF_FILE";

	//Symbols
	case TT_SEMICOLON:
        return "SEMICOLON";	  
	case TT_COMMA:
        return "COMMA";        
	case TT_PERIOD:
        return "PERIOD";
	case TT_ASSIGN:
		return "ASSIGN";		  
	case TT_POINTS:
        return "POINTS";        
	case TT_PAR1:
        return "PAR1";          
	case TT_PAR2:
        return "PAR2";          
    case TT_CHAV1:
        return "CHAV1";         
    case TT_CHAV2:
        return "CHAV2";
	case TT_QUOTE:
		return "QUOTE";         

	//Logic Operators
	case TT_EQUAL:
        return "EQUAL";		  
	case TT_NOT_EQUAL:
        return "NOT_EQUAL";     
	case TT_LOWER:
        return "LOWER";         
	case TT_GREATER:
        return "GREATER";       
	case TT_LESS_EQUAL:
        return "LESS_EQUAL";    
	case TT_GREATER_EQUAL:
        return "GREATER_EQUAL"; 

	// Conector Operators
	case TT_AND:
        return "AND";           
	case TT_OR:
        return "OR";            
    case TT_NOT:
        return "NOT";           

	// Arithmetic operators
	case TT_ADD:
        return "ADD";           
	case TT_SUB:
        return "SUB";          
	case TT_MUL:
        return "MUL";           
	case TT_DIV:
        return "DIV";           

	//Keywords
	case TT_CLASS:
        return "CLASS";		  
	case TT_IF:
        return "IF";            
	case TT_ELSE:
        return "ELSE";          
	case TT_WHILE:
        return "WHILE";         
	case TT_WRITE:
        return "WRITE";         
	case TT_READ:
        return "READ";          
	case TT_DO:
        return "DO";			  
	case TT_INT:
        return "INT";           
	case TT_FLOAT: 
        return "FLOAT";        
	case TT_STRING:
        return "STRING";        

	//Others
	case TT_ID:
        return "IDENTIFIER";          
	case TT_INTEGER:
        return "INTEGER";
	case TT_REAL:
        return "REAL";
	case TT_LITERAL:
        return "LITERAL";         
    default:
        throw std::string("invalid token type");         

    }
    
}

#endif