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
            ast::FunctionName*  _funcName = nullptr;
            ast::Id*            _id = nullptr;

      //      ~Name();
        }_name;
        struct Params{
            ast::Elements*      _elements = nullptr;
            ast::Id*            _id = nullptr;
            ast::Expression*    _expression = nullptr;

      //      ~Params();
        }_params;
    public:
        FunctionCall(){}
        //~FunctionCall(){};
        FunctionCall(ast::Id& id, ast::Elements& elements);
        FunctionCall(ast::Id& id, ast::Id& id1, ast::Expression& expression);
        FunctionCall(ast::FunctionName& functionName, ast::Elements& elements);
        FunctionCall(ast::FunctionName& functionName, ast::Id& id1, ast::Expression& expression);
    };
}


#endif //LISTLANGUAGE_FUNCTIONCALL_H
