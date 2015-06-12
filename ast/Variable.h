//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_VARIABLE_H
#define LISTLANGUAGE_VARIABLE_H

#include "Type.h"
#include "Id.h"

namespace ast {

    struct Variable {
        ast::Type   _type;
        ast::Id     _id;
        Variable(ast::Type t, ast::Id i) : _type(t), _id(i) {}
        Variable(){}
     //   ~Variable(){};
    };
}


#endif //LISTLANGUAGE_VARIABLE_H
