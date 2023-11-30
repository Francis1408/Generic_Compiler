#include "MulopExpr.h"


MulopExpr::MulopExpr(int line, enum MulopExpr::Op op)  { 
    this->m_line = line;
    this->m_op = op;

}

MulopExpr::~MulopExpr() {

}
