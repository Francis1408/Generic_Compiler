#include "AddopExpr.h"


AddopExpr::AddopExpr(int line, enum AddopExpr::Op op)  { 
    this->m_line = line;
    this->m_op = op;

}

AddopExpr::~AddopExpr() {

}
