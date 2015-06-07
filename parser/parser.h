//
// Created by agata on 07.06.15.
//

#ifndef LISTLANGUAGE_PARSER_H
#define LISTLANGUAGE_PARSER_H


#include "scanner/scanner.h"
#include "../ast/Flag.h"
#include "../ast/Type.h"
#include "../ast/Id.h"
#include "../ast/Range.h"

class parser {
    std::vector<void*> ast;

public:
    void parse(std::string);
    ~parser();
    void tryVarDeclaration(std::vector<tokenType>::iterator*, std::vector<std::string>::iterator*);
    ast::Type tryType(tokenType);
    ast::Id tryAssignVar(tokenType, std::string);
    ast::Range tryRange(std::vector<tokenType>::iterator*, std::vector<std::string>::iterator*);
};


#endif //LISTLANGUAGE_PARSER_H
