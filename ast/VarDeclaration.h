//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_VARDECLARATION_H
#define LISTLANGUAGE_VARDECLARATION_H

#include "Variable.h"
#include "Operator.h"
#include "Expression.h"
#include "ListGetter.h"

namespace ast {

    class AssignVar{
        ast::Id     _id;
        struct rightOperand{
            int*    _int;
            float*  _float;
            ast::Id*    _id;
            ast::Expression* _expression;
            ast::ListGetter*    _listGetter;
        }_rightOperand;
    };

    class VarDeclaration {
        ast::Type   _type;
        ast::AssignVar  _assignVar;

    };
}

#endif //LISTLANGUAGE_VARDECLARATION_H
