//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_ELEMENTS_H
#define LISTLANGUAGE_ELEMENTS_H

#include "Id.h"
#include <vector>

namespace ast {

    class Elements {

        class Element{
            int* _int = nullptr;
            float* _float = nullptr;
            ast::Id* _id = nullptr;

        public:
            Element(int i) : _int(new int(i)){};
            Element(float f) : _float(new float(f)){}
            Element(ast::Id id) : _id(new ast::Id(id)){}
        };


        std::vector<Element> _elements;
    };
}


#endif //LISTLANGUAGE_ELEMENTS_H
