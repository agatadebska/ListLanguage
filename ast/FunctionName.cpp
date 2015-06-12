//
// Created by agata on 05.06.15.
//

#include "FunctionName.h"

ast::FunctionName ast::functionNameFromString(std::string& name){
    if(name == "map")
        return ast::FunctionName::Map;
    else if(name == "filter")
        return ast::FunctionName::Filter;
    else if(name == "merge")
        return ast::FunctionName::Merge;
    else if(name == "length")
        return ast::FunctionName::Length;
    else if(name == "print")
        return ast::FunctionName::Print;
}