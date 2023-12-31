#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H

#include "SymbolTable.h"
#include "Lexeme.h"

class LexicalAnalysis {
    public:
        LexicalAnalysis(const char* filename);
        virtual ~LexicalAnalysis();

        Lexeme nextToken();
        int line() const {return m_line;}

        void showTable();
        bool addToken(std::string& token, std::string type);
        TableInfo* findToken(const std::string& token);

    private:
        int m_line;
        SymbolTable m_st;
        FILE* m_input;
};

#endif