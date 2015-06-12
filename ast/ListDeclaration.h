//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_LISTDECLARATION_H
#define LISTLANGUAGE_LISTDECLARATION_H

#include "Variable.h"
#include "Elements.h"
#include "Range.h"
#include "FunctionCall.h"

namespace ast {

    class ListDeclaration {
        ast::Variable   _variable;

        struct rightOperand {
            ast::Elements *_elements;
            ast::Id *_id;
            ast::Range *_range;
            ast::FunctionCall*  _functionCall;

     //       ~rightOperand();
        }_rightOperand;

    public:
        ListDeclaration(){};
     //   ~ListDeclaration(){};
        ListDeclaration(ast::Variable& variable, ast::Elements& elements);
        ListDeclaration(ast::Variable& variable, ast::Id& id);
        ListDeclaration(ast::Variable& variable, ast::Id& id, ast::Range& range);
        ListDeclaration(ast::Variable& variable, ast::FunctionCall& functionCall);
    };
}


#endif //LISTLANGUAGE_LISTDECLARATION_H
