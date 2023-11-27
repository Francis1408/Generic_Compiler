#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>
#include "TokenType.h"
#include "TableInfo.h"

class SymbolTable {
    public:
        SymbolTable();
        virtual ~SymbolTable();

        bool contains(const std::string& token) const;
        enum TokenType find(const std::string& token);
        void addId(const std::string& token);
        void showTable() const;

    private:
        std::map<std::string, TableInfo* > m_symbols;
};

#endif