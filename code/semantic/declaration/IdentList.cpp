#include "IdentList.h"
#include <iostream>

IdentList::IdentList(int m_line) {
    this->m_line = m_line;
}

IdentList::~IdentList(){

}

void IdentList::addId(Identifier* id) {
    this->idList.push_back(id);
}

void IdentList::showList() {
    int counter = 1;
    for(std::list<Identifier*>::iterator it = this->idList.begin(),
        ed = this->idList.end(); it != ed; it++, counter++) {
            Identifier* i = *it;
            std::cout << "Identifier(" << counter << "): "<< i->id << std::endl;
        }
}

