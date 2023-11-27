#include "TokenType.h"
#include "TableInfo.h"
#include <string>

TableInfo::TableInfo(TokenType token,std::string type){
    this->token = token;
    this->type = type;
}

TableInfo::~TableInfo(){

}

     