//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_ELEMENTS_H
#define LISTLANGUAGE_ELEMENTS_H

#include "Id.h"
#include <vector>

#include "Literal.h"

namespace ast {

    class Element{
        ast::Literal*   _literal = nullptr;
        ast::Id* _id = nullptr;

    public:
        Element(std::string& val);
    };

    class Elements {
        std::vector<Element> _elements;
    public:
        void addNextElement(Element&);
    };
}


#endif //LISTLANGUAGE_ELEMENTS_H
