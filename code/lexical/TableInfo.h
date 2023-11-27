#ifndef TABLE_INFO_H
#define TABLE_INFO_H


#include "TokenType.h"
#include <string>

class TableInfo {
    public:
        TableInfo(TokenType token,std::string type);
        virtual ~TableInfo();

        enum TokenType token;
        std::string type;
};

#endif