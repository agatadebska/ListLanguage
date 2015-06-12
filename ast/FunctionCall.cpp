//
// Created by agata on 05.06.15.
//

#include "FunctionCall.h"


ast::FunctionCall::FunctionCall(ast::Id& id, ast::Elements& elements){
    _name._id = new ast::Id(id);
    _params._elements = new ast::Elements(elements);
}
ast::FunctionCall::FunctionCall(ast::Id& id, ast::Id& id1, ast::Expression& expression){
    _name._id = new ast::Id(id);
    _params._id = new ast::Id(id1);
    _params._expression = new ast::Expression(expression);
}
ast::FunctionCall::FunctionCall(ast::FunctionName& functionName, ast::Elements& elements){
    _name._funcName = new ast::FunctionName(functionName);
    _params._elements = new ast::Elements(elements);
}
ast::FunctionCall::FunctionCall(ast::FunctionName& functionName, ast::Id& id1, ast::Expression& expression){
    _name._funcName = new ast::FunctionName(functionName);
    _params._id = new ast::Id(id1);
    _params._expression = new ast::Expression(expression);
}
/*
ast::FunctionCall::Name::~Name(){
    if(_id != nullptr)
        delete _id;
    if(_funcName != nullptr)
        delete _funcName;
}

ast::FunctionCall::Params::~Params(){
    if(_id != nullptr)
        delete _id;
    if(_elements != nullptr)
        delete _elements;
    if(_expression != nullptr)
        delete _expression;
}
*/