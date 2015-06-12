//
// Created by agata on 10.06.15.
//

#include "Literal.h"

/*
ast::Literal::~Literal(){
    if(integer!= nullptr)
        delete integer;
    if(floating!= nullptr)
        delete floating;
}
*/

bool ast::isInteger(std::string& value){
        if(!isdigit(value[0]))
            return false;
        if(value.find('.') == std::string::npos)
            return true;
        return false;
}

bool ast::isFloat(std::string& value){
    if(!isdigit(value[0]))
        return false;
    if(value.find('.') == std::string::npos)
        return false;
    return true;
}
