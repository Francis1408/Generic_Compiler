#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>

class Identifier {
    public:
        Identifier(std::string id, int m_line);
        virtual ~Identifier();

        std::string id;
        int m_line;

};

#endif