//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_BLOCKSTATEMENT_H
#define LISTLANGUAGE_BLOCKSTATEMENT_H

#include <vector>
#include "ListDeclaration.h"
#include "VarDeclaration.h"
#include "ReturnStatement.h"
#include "ForStatement.h"

namespace  ast {

    class IfStatement;
    class ElseStatement;

    class Operation{
        ast::ListDeclaration*   _listDeclaration;
        ast::IfStatement*       _ifStatement;
        std::vector<ast::ElseStatement> _elseStatement;
        ast::ForStatement*      _forStatement;
        ast::AssignVar*          _assignVar;
        ast::VarDeclaration*    _varDeclaration;
        ast::FunctionCall*      _functionCall;
        ast::ReturnStatement*   _returnStatement;
    };

    class Statement {
        std::vector<Operation>  _operations;
    };

    class IfStatement {
        ast::Expression _expression;
        ast::Statement _blockStatement;
    };

    class ElseStatement{
        ast::IfStatement*   _ifStatement;
        ast::Statement *    _blockStatement;
    };

}


#endif //LISTLANGUAGE_BLOCKSTATEMENT_H
