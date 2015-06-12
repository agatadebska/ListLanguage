//
// Created by agata on 05.06.15.
//

#include "Statement.h"


ast::Operation::Operation(ast::ListDeclaration& listDeclaration) : _listDeclaration(new ast::ListDeclaration(listDeclaration)){}
ast::Operation::Operation(ast::IfStatement& ifStatement) : _ifStatement(new ast::IfStatement(ifStatement)){}
ast::Operation::Operation(ast::ForStatement& forStatement) : _forStatement(new ast::ForStatement(forStatement)){}
ast::Operation::Operation(ast::AssignVar& assignVar) : _assignVar(new ast::AssignVar(assignVar)){}
ast::Operation::Operation(ast::VarDeclaration& varDeclaration) : _varDeclaration(new ast::VarDeclaration(varDeclaration)){}
ast::Operation::Operation(ast::FunctionCall& functionCall) : _functionCall(new ast::FunctionCall(functionCall)){}
ast::Operation::Operation(ast::FunctionDeclaration& functionDeclaration): _functionDeclaration(new ast::FunctionDeclaration(functionDeclaration)){}
ast::Operation::Operation(ast::Expression& expression):_expression(new ast::Expression(expression)){};
ast::Operation::Operation(ast::ReturnStatement& returnStatement) : _returnStatement(new ast::ReturnStatement(returnStatement)){};

void ast::Operation::addElseStatement(ast::ElseStatement& elseStatement){
    _elseStatement.push_back(elseStatement);
}

ast::ElseStatement::ElseStatement(ast::IfStatement& ifStatement): _ifStatement(new ast::IfStatement(ifStatement)){}
ast::ElseStatement::ElseStatement(ast::Statement& statement):_blockStatement(new ast::Statement(statement)){}

void ast::Statement::addOperation(ast::Operation& operation){
    _operations.push_back(operation);
}


void ast::ForStatement::addInitId(ast::Id& id){
    _initialization._id = new ast::Id(id);
}
void ast::ForStatement::addInitVarDeclaration(ast::VarDeclaration& varDeclaration){
    _initialization._varDeclaration = new ast::VarDeclaration(varDeclaration);
}
void ast::ForStatement::addInitExpression(ast::Expression& expression){
    _initialization._expression = new ast::Expression(expression);
}
void ast::ForStatement::addCondition(ast::Expression& expression) {
    _condition._expression = expression;
}
void ast::ForStatement::addIncrement(ast::Id& id, ast::Expression& expression){
    _increment._id = id;
    _increment._expression = expression;
}
void ast::ForStatement::addStatement(ast::Statement& statement){
    _statement = statement;
}
/*

ast::ForStatement::Initialization::~Initialization(){
    if(_id != nullptr)
        delete _id;
    if(_expression != nullptr)
        delete _expression;
    if(_varDeclaration != nullptr)
        delete _varDeclaration;
}*/
/*
ast::Operation::~Operation(){
    if(_listDeclaration != nullptr)
        delete _listDeclaration;
    if(_varDeclaration != nullptr)
        delete _varDeclaration;
    if(_functionCall != nullptr)
        delete _functionCall;
    if(_assignVar != nullptr)
        delete _assignVar;
    if(_forStatement != nullptr)
        delete _forStatement;
    if(_ifStatement != nullptr)
        delete _ifStatement;
}
ast::ElseStatement::~ElseStatement() {
    if(_ifStatement != nullptr)
        delete _ifStatement;
    if(_blockStatement != nullptr)
        delete _blockStatement;
}
 */


void ast::Parameters::addParameter(ast::Variable& variable){
    _variables.push_back(variable);
}

ast::FunctionDeclaration::FunctionDeclaration(ast::Id& id, ast::Type type, ast::Parameters& parameters, ast::Statement& statement){
    _id = id;
    _type = new ast::Type(type);
    _parameters = parameters;
    _blockStatement = statement;
}
ast::FunctionDeclaration::FunctionDeclaration(ast::Id& id, ast::Parameters& parameters, ast::Statement& statement){
    _id = id;
    _parameters = parameters;
    _blockStatement = statement;
}
/*
ast::FunctionDeclaration::~FunctionDeclaration(){
    if(_type != nullptr)
        delete _type;
}
*/