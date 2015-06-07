//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_FUNCTIONCALL_H
#define LISTLANGUAGE_FUNCTIONCALL_H

#include "FunctionName.h"
#include "Id.h"
#include "Elements.h"
#include "Expression.h"

namespace ast {

    class FunctionCall {
        struct Name{
            ast::FunctionName*  _funcName;
            ast::Id*            _id;
        };
        struct Params{
            ast::Elements*      _elements;
            ast::Id*            _id;
            ast::Expression*    _expression;
        };
    };
}


#endif //LISTLANGUAGE_FUNCTIONCALL_H
