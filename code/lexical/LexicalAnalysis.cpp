#include "LexicalAnalysis.h"
#include <string.h>
#include <cctype>

LexicalAnalysis::LexicalAnalysis(const char* filename) : m_line(1) {
    m_input = fopen(filename, "r");
}

LexicalAnalysis::~LexicalAnalysis() {
    if (m_input != nullptr)
        fclose(m_input);
}

Lexeme LexicalAnalysis::nextToken() {
    int state;
    Lexeme lex;

    state = 1;
    while(state != 15 && state != 16) {
        int c = fgetc(m_input);

        switch (state)
        {
        case 1:
            break;
        case 2:
            if (c == '/') {
                state = 3;
            } else if(c == '*'){
                state = 4;
            } else {
                if (c != -1) 
                    ungetc(c, m_input);
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
                state = 4;
            }
            break;
        case 5:
            if (c == '/') {
                state = 1;
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

                lex.type = TT_CONST;
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

                lex.type = TT_CONST;
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
                
                lex.type = TT_CONST;
                state = 16;
            }
            break;
        case 14:
        if(c != '”') {
            lex.token += (char) c;
            state = 14;
        } else {
            lex.token += (char) c;
            lex.type = TT_CONST;
            state = 16;
        }
        break;
        default:
            throw std::string("invalid state");
        }
        
    }
    if (state == 15 || state == 16) {
        lex.type = m_st.find(lex.token);
    }

    return lex;
}
