//
// Created by agata on 05.06.15.
//

#include "VarDeclaration.h"


ast::AssignVar::AssignVar(ast::Id& id, std::string& val){
    _id = id;
    if(isInteger(val)) {
        int i = stoi(val);
        _rightOperand._literal = new ast::Literal(i);
    }
    else if(isFloat(val)) {
        float f = stof(val);
        _rightOperand._literal = new ast::Literal(f);
    }
    else
        _rightOperand._id = new Id(val);
}
ast::AssignVar::AssignVar(ast::Id& id, ast::Expression& expression){
    _id = id;
    _rightOperand._expression = new Expression(expression);
}
ast::AssignVar::AssignVar(ast::Id& id, ast::ListGetter& listGetter){
    _id = id;
    _rightOperand._listGetter = new ListGetter(listGetter);
}
ast::AssignVar::AssignVar(ast::Id& id, ast::FunctionCall& functionCall){
    _id = id;
    _rightOperand._functionCall = new ast::FunctionCall(functionCall);
}

std::string ast::AssignVar::getId(){
    return _id;
}
/*
ast::AssignVar::rightOperand::~rightOperand(){
    if(_listGetter != nullptr)
        delete _listGetter;
    if(_id != nullptr)
        delete _id;
    if(_literal != nullptr)
        delete _literal;
    if(_expression != nullptr)
        delete _expression;
    if(_functionCall != nullptr)
        delete _functionCall;
}
 */