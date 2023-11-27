#include "ExprType.h"

#include <string>

ExprType::ExprType(std::string type, int line) {
    this->type = type;
    this->m_line = line;
}

ExprType::~ExprType() {}

