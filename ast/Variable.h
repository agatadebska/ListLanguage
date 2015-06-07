//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_VARIABLE_H
#define LISTLANGUAGE_VARIABLE_H

#include "Type.h"
#include "Id.h"

namespace ast {

    class Variable {
        ast::Type   _type;
        ast::Id     _id;
    public:
        Variable(ast::Type t, ast::Id i) : _type(t), _id(i) {}
    };
}


#endif //LISTLANGUAGE_VARIABLE_H
