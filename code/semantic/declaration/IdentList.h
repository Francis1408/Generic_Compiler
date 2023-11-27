#ifndef IDENT_LIST_H
#define IDENT_LIST_H

#include <list>
#include "Identifier.h"

class IdentList {
    public:
        IdentList(int m_line);
        virtual ~IdentList();

        void addId(Identifier* id);
        void showList();

        int m_line;
        std::list <Identifier*> idList;

};

#endif