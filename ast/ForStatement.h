//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_FORSTATEMENT_H
#define LISTLANGUAGE_FORSTATEMENT_H

#include "Id.h"
#include "VarDeclaration.h"

namespace ast {

    class ForStatement {
        struct Initialization{
            ast::Id*    _id;
            ast::VarDeclaration*    _varDeclaration;
            ast::Expression*     _expression;
        }_initialization;
        struct Condition{
            ast::Expression    _expression;
        }_condition;
        struct Increment{
            ast::Id     _id;
            ast::Expression _expression;
        }_increment;
    };
}
#endif //LISTLANGUAGE_FORSTATEMENT_H
