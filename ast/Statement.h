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
#include "FunctionDeclaration.h"

namespace  ast {

    class IfStatement;
    class ElseStatement;
    class FunctionDeclaration;
    class ForStatement;

    class Operation{
        ast::ListDeclaration*   _listDeclaration = nullptr;
        ast::IfStatement*       _ifStatement = nullptr;
        std::vector<ast::ElseStatement> _elseStatement;
        ast::ForStatement*      _forStatement = nullptr;
        ast::AssignVar*          _assignVar = nullptr;
        ast::VarDeclaration*    _varDeclaration = nullptr;
        ast::FunctionCall*      _functionCall = nullptr;
        ast::FunctionDeclaration* _functionDeclaration = nullptr;
        ast::Expression*        _expression = nullptr;
        ast::ReturnStatement*   _returnStatement = nullptr;
    public:
        Operation(){}
      //  ~Operation();
        Operation(ast::ListDeclaration&);
        Operation(ast::IfStatement&);
        Operation(ast::ForStatement&);
        Operation(ast::AssignVar&);
        Operation(ast::VarDeclaration&);
        Operation(ast::FunctionCall&);
        Operation(ast::FunctionDeclaration&);
        Operation(ast::Expression&);
        Operation(ast::ReturnStatement&);
        void addElseStatement(ast::ElseStatement&);
    };

    struct Statement {
        std::vector<Operation>  _operations;            //moze byc puste
    //    ~Statement(){};
        void addOperation(ast::Operation& operation);
    };

    class IfStatement {
        ast::Expression _expression;
        ast::Statement _blockStatement;
    public:
        IfStatement(){};
    //    ~IfStatement(){};
        IfStatement(ast::Expression& expression, ast::Statement& statement) : _expression(expression),
                                                                              _blockStatement(statement){}
    };

    class ElseStatement{
        ast::IfStatement*   _ifStatement;
        ast::Statement *    _blockStatement;
    public:
        ElseStatement(){}
     //   ~ElseStatement();
        ElseStatement(ast::IfStatement&);
        ElseStatement(ast::Statement&);
    };


    class Parameters{
        std::vector<ast::Variable>  _variables;
    public:
        Parameters(){}
        //   ~Parameters(){}
        void addParameter(ast::Variable& variable);
    };

    class FunctionDeclaration {
        ast::Id _id;
        ast::Type*   _type;
        ast::Parameters     _parameters;
        ast::Statement _blockStatement;
    public:
        FunctionDeclaration(){};
        //  ~FunctionDeclaration();
        FunctionDeclaration(ast::Id& id, ast::Type type, ast::Parameters&, ast::Statement&);
        FunctionDeclaration(ast::Id& id, ast::Parameters&, ast::Statement&);

    };


    class ForStatement {
        struct Initialization{
            ast::Id*    _id;
            ast::VarDeclaration*    _varDeclaration;
            ast::Expression*     _expression;

            //        ~Initialization();
        }_initialization;
        struct Condition{
            ast::Expression    _expression;
        }_condition;
        struct Increment{
            ast::Id     _id;
            ast::Expression _expression;
        }_increment;

        ast::Statement _statement;

    public:
        ForStatement(){}
        void addInitId(ast::Id&);
        void addInitVarDeclaration(ast::VarDeclaration&);
        void addInitExpression(ast::Expression&);
        void addCondition(ast::Expression&);
        void addIncrement(ast::Id&, ast::Expression&);
        void addStatement(ast::Statement&);
        //   ~ForStatement(){};
    };



}


#endif //LISTLANGUAGE_BLOCKSTATEMENT_H
