//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_FUNCTIONDECLARATION_H
#define LISTLANGUAGE_FUNCTIONDECLARATION_H

#include "Id.h"
#include "Type.h"
#include "Variable.h"
#include "Statement.h"
#include <vector>

namespace ast {

    class Parameters{
        std::vector<ast::Variable>  _variables;
    };

    class FunctionDeclaration {
        ast::Id _id;
        ast::Type*   _type;
        ast::Parameters     _parameters;
        ast::Statement _blockStatement;
    };



}


#endif //LISTLANGUAGE_FUNCTIONDECLARATION_H
