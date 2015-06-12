//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_VARDECLARATION_H
#define LISTLANGUAGE_VARDECLARATION_H

#include "Variable.h"
#include "Operator.h"
#include "Expression.h"
#include "ListGetter.h"
#include "Literal.h"
#include "FunctionCall.h"

namespace ast {

    class AssignVar{
        ast::Id     _id;
        struct rightOperand{
            ast::Literal* _literal = nullptr;
            ast::Id*    _id = nullptr;
            ast::Expression* _expression = nullptr;
            ast::ListGetter*    _listGetter = nullptr;
            ast::FunctionCall*  _functionCall = nullptr;
      //      ~rightOperand();
        }_rightOperand;

    public:
        AssignVar(){}
        AssignVar(ast::Id&, std::string&);              //assign literal or id
        AssignVar(ast::Id&, ast::Expression&);
        AssignVar(ast::Id&, ast::ListGetter&);
        AssignVar(ast::Id&, ast::FunctionCall&);
        std::string getId();
     //   ~AssignVar(){};
    };

    class VarDeclaration {
        ast::Type   _type;
        ast::AssignVar  _assignVar;

    public:
        VarDeclaration(){};
     //   ~VarDeclaration(){};
        VarDeclaration(ast::Type type, ast::AssignVar assignVar) : _type(type), _assignVar(assignVar){}

    };
}

#endif //LISTLANGUAGE_VARDECLARATION_H
