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
#include "../ast/VarDeclaration.h"
#include "../ast/Elements.h"
#include "../ast/FunctionCall.h"
#include "../ast/FunctionDeclaration.h"


enum symbolType : int{
    Integer,
    Floating,
    IntFunc,
    IntListFunc,
    FloatFunc,
    FloatListFunc,
    IntList,
    FloatList,
};

enum scopeType : int{
    global,
    funcParam,
    blockLocal,
    forStatement,
};

class parser {
    ast::Statement program;
    std::vector<std::pair<tokenType, std::string>>::iterator start;
    std::vector<std::pair<tokenType, std::string>>::iterator end;
    struct Symbol{
        std::string name;
        symbolType type;
        scopeType scope;
    };
    vector<Symbol> symbols;
    bool errored = false;

public:
    void parse(std::string);
    ~parser(){};
    ast::VarDeclaration tryVarDeclaration(std::vector<std::pair<tokenType, std::string>>::iterator*, scopeType scope);
    ast::Type tryType(std::vector<std::pair<tokenType, std::string>>::iterator*);
    ast::Range tryRange(std::vector<std::pair<tokenType, std::string>>::iterator*);
    ast::Variable tryVariable(std::vector<std::pair<tokenType, std::string>>::iterator*);
    ast::MultiplicativeExpression tryMultiplicativeExpression(std::vector<std::pair<tokenType, std::string>>::iterator*, ast::MultiplicativeExpression* expr);
    ast::AdditiveExpression tryAdditiveExpression(std::vector<std::pair<tokenType, std::string>>::iterator*, ast::AdditiveExpression*);
    ast::RelationalExpression tryRelationalExpression(std::vector<std::pair<tokenType, std::string>>::iterator*, ast::RelationalExpression*);
    ast::EqualityExpression tryEqualityExpression(std::vector<std::pair<tokenType, std::string>>::iterator*, ast::EqualityExpression*);
    ast::AndExpression tryAndExpression(std::vector<std::pair<tokenType, std::string>>::iterator*, ast::AndExpression*);
    ast::Expression tryExpression(std::vector<std::pair<tokenType, std::string>>::iterator*, ast::Expression*);
    ast::AssignVar tryAssignVar(std::vector<std::pair<tokenType, std::string>>::iterator*);
    ast::Elements tryElements(std::vector<std::pair<tokenType, std::string>>::iterator*);
    ast::ListGetter tryListGetter(std::vector<std::pair<tokenType, std::string>>::iterator*);
    ast::FunctionCall tryFunctionCall(std::vector<std::pair<tokenType, std::string>>::iterator*);
    ast::FunctionName tryFunctionName(std::vector<std::pair<tokenType, std::string>>::iterator*);
    ast::Parameters tryParameters(std::vector<std::pair<tokenType, std::string>>::iterator*, scopeType scope);
    ast::IfStatement tryIfStatement(std::vector<std::pair<tokenType, std::string>>::iterator*, scopeType scope);
    ast::ElseStatement tryElseStatement(std::vector<std::pair<tokenType, std::string>>::iterator*, scopeType scope);
    ast::ReturnStatement tryReturnStatement(std::vector<std::pair<tokenType, std::string>>::iterator*);
    ast::Statement tryStatement(std::vector<std::pair<tokenType, std::string>>::iterator*, scopeType scope);
    ast::ForStatement tryForStatement(std::vector<std::pair<tokenType, std::string>>::iterator*);
    ast::Operation tryOperation(std::vector<std::pair<tokenType, std::string>>::iterator*, scopeType scope);
    ast::FunctionDeclaration tryFunctionDeclaration(std::vector<std::pair<tokenType, std::string>>::iterator*, scopeType scope);
    ast::ListDeclaration tryListDeclaration(std::vector<std::pair<tokenType, std::string>>::iterator*, scopeType scope);
    void showError(tokenType& token, std::string errElem, std::string str, std::string expect);

    int addSymbol(std::string name, symbolType type, scopeType scope);

    int semanticAnalysis();
};


#endif //LISTLANGUAGE_PARSER_H
