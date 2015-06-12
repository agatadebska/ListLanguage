//
// Created by agata on 05.06.15.
//

#include "Elements.h"

void ast::Elements::addNextElement(Element& e){
    _elements.push_back(e);
}

ast::Element::Element(std::string& val){
    if(ast::isInteger(val))
        _literal = new Literal(stoi(val));
    else if(ast::isFloat(val))
        _literal = new Literal(stof(val));
    else
        _id = new ast::Id(val);
}
/*
ast::Elements::~Elements() {

    if(_literal != nullptr)
        delete _literal;
    if(_id != nullptr)
        delete _id;
}
*/