//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_SCANNER_H
#define LISTLANGUAGE_SCANNER_H

#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include "../../ioModule/ioModule.h"


enum tokenType : int{
    Id,                 // 0
    IntVal,             // 1
    FloatVal,           // 2
    MultiplOp,          // 3
    AdditiveOp,         // 4
    RelationalOp,       // 5
    EqualOp,            // 6
    FuncName,           // 7
    Int,
    Float,
    AndOp,
    OrOp,
    AssigOp,
    Comma,
    Dot,                // 20
    Colon,              //dwukropek
    Semicolon,          //srednik
    Var,
    If,
    Else,
    For,
    List,
    Func,
    Return,
    Arrow,
    ParentheseOpen,             // (
    ParentheseClose,            // )
    BraceOpen,                  // {
    BraceClose,                 // }
    SquareBraceOpen,            // [
    SquareBraceClose,           // ]
};



class scanner{
    std::vector<tokenType>  _tokensTypes;
    //std::vector<std::string> _tokens;
    std::vector<std::pair<tokenType, std::string>> _tokens;
    ioModule    _ioModule;
    std::string token = "";
  //  std::vector<std::string> tokens;
    char symbols[22];
    void ignoreWhitespaces();
    void addToken(tokenType);
    void tryV();                //what to do when token starts from 'v'
    void tryF();                //what to do when token starts from 'f'
    void tryI();                //what to do when token starts from 'i'
    void tryE();                //what to do when token starts from 'e'
    void tryR();                //what to do when token starts from 'r'
    void tryL();                //what to do when token starts from 'l'
    void tryP();
    void tryM();
    void tryId();
    void tryNumber();
    friend class parser;

public:
    scanner(){};
    scanner(std::string);
    void printTokens();
    int tokenize();

};

std::string toString(tokenType& tok);


#endif //LISTLANGUAGE_SCANNER_H
