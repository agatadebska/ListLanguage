//
// Created by agata on 07.06.15.
//

#include "parser.h"
#include "../ast/ListDeclaration.h"
#include "../ast/VarDeclaration.h"

void parser::parse(std::string fileName){
    scanner _scanner(fileName);
    _scanner.tokenize();

    std::vector<tokenType>::iterator tokenType = _scanner._tokensTypes.begin();
    std::vector<std::string>::iterator tokenValue = _scanner._tokens.begin();
    while(tokenType !=_scanner._tokensTypes.end()){
        std::cout << *tokenType << "        " << *tokenValue << std::endl;

        switch(*tokenType){
            case Var:
                tryVarDeclaration(tokenType, tokenValue);
                ast::VarDeclaration varDeclaration;
                ++tokenType; ++tokenValue;
                break;
            case Float:
                ast::Type type = ast::Type::Float;
                ++tokenType; ++tokenValue;
            case Int:
                ast::Type type = ast::Type::Float;
                ++tokenType; ++tokenValue;

        }


        ++tokenType;
        ++tokenValue;
    }
}

ast::Range tryRange(std::vector<tokenType>::iterator* type, std::vector<std::string>::iterator* value){
    if(**type == SquareBraceOpen){
        ++(*type), ++(*value);
    }
}

void parser::tryVarDeclaration(std::vector<tokenType>::iterator* i, std::vector<std::string>::iterator* j){
    ast::VarDeclaration varDeclaration;
    ++(*i); ++(*j);
    ast::Type type1 = tryType(**i);
    ++(*i); ++(*j);

}

ast::Type parser::tryType(tokenType tok){
    if(tok == Int)
        return ast::Type::Int;
    else if(tok == Float)
        return ast::Type::Float;
    else {
        std::cerr << "Zly typ danych" << std::endl;
        exit(1);
    }
}

ast::Id parser::tryAssignVar(tokenType type, std::string value){
    if(type == Id)
        return ast::Id(value);
    else{
        std::cerr << "Brak nazwy zmiennej" << std::endl;
        exit(1);
    }
}

parser::~parser(){
    std::vector<void*>::iterator i = ast.begin();
    for(i; i != ast.end(); ++i){
        if(*i != nullptr)
            delete *i;
    }
}