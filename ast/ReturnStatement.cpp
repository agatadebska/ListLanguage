//
// Created by agata on 05.06.15.
//

#include "ReturnStatement.h"

ast::ReturnStatement::ReturnStatement(std::string& val){
    if(isInteger(val))
        _literal = new Literal(stoi(val));
    else if(isFloat(val))
        _literal = new Literal(stof(val));
    else
        _id = new ast::Id(val);
}
/*
ast::ReturnStatement::~ReturnStatement(){
    if (_id != nullptr)
        delete _id;
    if(_literal != nullptr)
        delete _literal;
}

*/