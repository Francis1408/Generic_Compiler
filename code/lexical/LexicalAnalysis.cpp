#include "LexicalAnalysis.h"
#include <iomanip>
#include <string.h>
#include <cctype>
#include <iostream>

LexicalAnalysis::LexicalAnalysis(const char* filename) : m_line(1) {
    m_input = fopen(filename, "r");
}

LexicalAnalysis::~LexicalAnalysis() {
    if (m_input != nullptr)
        fclose(m_input);
}
void LexicalAnalysis::showTable() {
    std::cout << "---------TABELA DE SÍMBOLOS---------" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << std::setw(15) << "LEXEMA";
    std::cout << std::setw(2) << " ";
    std::cout << "|";
    std::cout << std::setw(2) << " "; 
    std::cout << std::setw(4) << "TOKEN ID" << std::endl;
    this->m_st.showTable();
}

Lexeme LexicalAnalysis::nextToken() {
    int state;
    Lexeme lex;

    state = 1;

    while(state != 15 && state != 16) {
        int c = fgetc(m_input);

       // std::cout << "[" << state << ", " << c << " ('" 
       //           << (char) c << "')]" << std::endl;
        switch (state)
        {
        case 1:
            if (c == ' ' || c == '\t' || c == '\r') {
                state = 1;
            } else if (c == '\n') {
                m_line++;
                state = 1;
            } else if (c == '/') {
                lex.token += (char) c;
                state = 2;
            } else if (c == '=' || c == '<' || c == '>' || c == '!') {
                lex.token += (char) c;
                state = 6;
            } else if (c == '+' || c == ',' || c == ';' || c == '(' || c == ')' || 
                       c == '{' || c == '}' || c == '*' || c == '-' || c == '.') {
                lex.token += (char) c;
                state = 15;
            } else if (c == '&') {
                lex.token += (char) c;
                state = 8;
            } else if (c == '|') {
                lex.token += (char) c;
                state = 9;
            } else if (isalpha(c)) {
                lex.token += (char) c;
                state = 7;
            } else if (isdigit(c) && c != '0') {
                lex.token += (char) c;
                state = 10;
            } else if (c == '0') {
                lex.token += (char) c;
                state = 13;
            } else if (c == '"') {
                lex.token += (char) c;
                state = 14;
            } else {
                if (c == -1) {
                    lex.type = TT_END_OF_FILE;
                    state = 16;
                } else {
                    lex.token += (char) c;
                    lex.type = TT_INVALID_TOKEN;
                    state = 16;
                }
            }
            break;
        case 2:
            if (c == '/') {
                state = 3;
                lex.token = "";
            } else if(c == '*'){
                state = 4;
                lex.token = "";
            } else {
                if (c != -1) {
                    ungetc(c, m_input);
                }
                    
                state = 15;
            }
            break;
        case 3:
            if (c == '\n') {
                m_line++;
                state = 1;
            } else if (c == -1) {
                lex.type = TT_END_OF_FILE;
                state = 16;
            } else {
                state = 3;
            }
            break;
        case 4:
            if (c == '*') {
                state = 5;
            } else {
                if(c != -1)
                    state = 4;
                else {
                    lex.type = TT_END_OF_FILE;
                    state = 16;
                }
                    
            }
            break;
        case 5:
            if (c == '/') {
                state = 1;
            } else if (c == '*') {
                state = 5;
            } else {
                state = 4;
            }
            break;
        case 6:
            if (c == '=') {
                lex.token += (char) c;
                state = 15;
            } else {
                if (c != -1) 
                    ungetc(c, m_input);

                state = 15;
            }
            break;
        case 7:
            if (c == '_' ||isalpha(c) || isdigit(c)) {
                lex.token += (char) c;
                state = 7;
            } else {
                if (c != -1) 
                    ungetc(c, m_input);
                state = 15;
            }
            break;
        case 8:
            if (c == '&') {
                lex.token += (char) c;
                state = 15;
            } else {
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 16; 
                } else {
                    lex.type = TT_INVALID_TOKEN;
                    state = 16;
                }
            }
            break;
        case 9:
            if (c == '|') {
                lex.token += (char) c;
                state = 15;
            } else {
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 16; 
                } else {
                    lex.type = TT_INVALID_TOKEN;
                    state = 16;
                }
            }
            break;
        case 10:
            if (isdigit(c)) {
                lex.token += (char) c;
                state = 10;
            } else if (c == '.') {
                lex.token += (char) c;
                state = 11;
            } else {
                if (c != -1) 
                    ungetc(c, m_input);

                lex.type = TT_INTEGER;
                state = 16;
            }
            break;
        case 11:
            if(isdigit(c)) {
                lex.token += (char) c;
                state = 12;
            } else {
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 16; 
                } else {
                    lex.type = TT_INVALID_TOKEN;
                    state = 16;
                }
            }
            break;
        case 12:
            if (isdigit(c)) {
                lex.token += (char) c;
                state = 12;
            } else {
                if (c != -1)
                    ungetc(c, m_input);

                lex.type = TT_REAL;
                state = 16;
            }
            break;
        case 13:
            if(c == '.') {
                lex.token += (char) c;
                state = 11;
            } else {
                if(c != -1)
                    ungetc(c, m_input);
                
                lex.type = TT_INTEGER;
                state = 16;
            }
            break;
        case 14:
        if(c != '"') {
            lex.token += (char) c;
            state = 14;
        } else {
            lex.token += (char) c;
            lex.type = TT_LITERAL;
            state = 16;
        }
            break;
        default:
            throw std::string("invalid state");
        }
        
    }
    if (state == 15) {
        lex.type = m_st.find(lex.token);
    }

    return lex;
}
