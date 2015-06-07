//
// Created by agata on 05.06.15.
//

#include "Type.h"

std::string ast::toString(Type t){
    switch(t){
        case Type::Float:
            return "float";
        case Type::Int:
            return  "int";
    }
}