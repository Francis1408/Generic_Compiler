#ifndef DECLARATION_H
#define DECLARATION_H

#include <string>

class Declaration {
    public:
        Declaration(std::string type, int m_line);
        virtual ~Declaration();

        int m_line;
        std::string type;

};

#endif