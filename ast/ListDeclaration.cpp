//
// Created by agata on 05.06.15.
//

#include "ListDeclaration.h"


ast::ListDeclaration::ListDeclaration(ast::Variable& variable, ast::Elements& elements){
    _variable = variable;
    _rightOperand._elements = new ast::Elements(elements);
}
ast::ListDeclaration::ListDeclaration(ast::Variable& variable, ast::Id& id){
    _variable = variable;
    _rightOperand._id = new ast::Id(id);
}
ast::ListDeclaration::ListDeclaration(ast::Variable& variable, ast::Id& id, ast::Range& range){
    _variable = variable;
    _rightOperand._id = new ast::Id(id);
    _rightOperand._range = new ast::Range(range);
}
ast::ListDeclaration::ListDeclaration(ast::Variable& variable, ast::FunctionCall& functionCall){
    _variable = variable;
    _rightOperand._functionCall = new ast::FunctionCall(functionCall);
}
/*
ast::ListDeclaration::rightOperand::~rightOperand(){
    if(_elements != nullptr)
        delete _elements;
    if(_id != nullptr)
        delete _id;
    if(_functionCall != nullptr)
        delete _functionCall;
    if(_range != nullptr)
        delete _range;
}*/