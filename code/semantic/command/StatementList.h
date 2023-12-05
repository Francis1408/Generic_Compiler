#ifndef STATEMENT_LIST_H
#define STATEMENT_LIST_H

#include <list>

class ExprType;
class Statement;

class StatementList {
    public:
        StatementList(int m_line);
        virtual ~StatementList();

        void addStmt(Statement* id);
        void showList();
        ExprType* getType(); 

        int m_line;
        std::list <Statement*> stmtList;
        ExprType* m_type;

};

#endif