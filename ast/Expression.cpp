//
// Created by agata on 05.06.15.
//

#include "Expression.h"

ast::Operand::Operand(std::string& val){
    if(!isdigit(val[0])){
        _id = new ast::Id(val);
        return;
    }
    else if(val.find('.') == std::string::npos){
        _int = new int(std::stoi(val));
        return;
    }
    else
        _float = new float(std::stof(val));
}

ast::Operand::Operand(const Operand& op): _id(op._id), _int(op._int), _float(op._float){}
/*
ast::Operand::~Operand() {
    if(_id != nullptr) {
        delete _id;
        _id = nullptr;
    }
    if(_float != nullptr) {
        delete _float;
        _float = nullptr;
    }
    if(_int != nullptr) {
        delete _int;
        _int = nullptr;
    }
}

*/

bool ast::Operand::isGood(){
    return (_id!= nullptr || _float!= nullptr || _int!= nullptr);
}

bool ast::MultiplicativeExpression::isGood(){
    return _leftOperand.isGood();
}

bool ast::AdditiveExpression::isGood(){
    return _leftOperand.isGood();
}

bool ast:: RelationalExpression::isGood(){
    return _leftOperand.isGood();
}

bool ast::EqualityExpression::isGood(){
    return _leftOperand.isGood();
}

bool ast::AndExpression::isGood(){
    return _leftOperand.isGood();
}

bool ast::Expression::isGood(){
    return _leftOperand.isGood();
}

void ast::MultiplicativeExpression::addRightOperand(std::string oper, std::string val){
    ast::MultiplicativeOp multiplicativeOp;
    if(oper == "*")
        multiplicativeOp = ast::MultiplicativeOp::Multiplicate;
    else if(oper == "/")
        multiplicativeOp = ast::MultiplicativeOp::Divide;
    else if(oper == "%")
        multiplicativeOp = ast::MultiplicativeOp::Modulo;
    Operand o(val);
    _rightOperand.push_back(std::make_pair(multiplicativeOp, o));
}

void ast::AdditiveExpression::addRightOperand(std::string oper, ast::MultiplicativeExpression* expression){
    ast::AdditiveOp additiveOp;
    if(oper == "+")
        additiveOp = ast::AdditiveOp::Plus;
    else if(oper == "-")
        additiveOp = ast::AdditiveOp::Minus;
    _rightOperand.push_back(std::make_pair(additiveOp, *expression));
}

void ast::RelationalExpression::addRightOperand(std::string oper, ast::AdditiveExpression* expression){
    ast::RelationalOp relationalOp;
    if(oper == "<")
        relationalOp = ast::RelationalOp::Less;
    else if(oper == "<=")
        relationalOp = ast::RelationalOp::LessEqual;
    else if(oper == ">")
        relationalOp = ast::RelationalOp::Greater;
    else if(oper == ">=")
        relationalOp = ast::RelationalOp::GreaterEqual;
    _rightOperand.push_back(std::make_pair(relationalOp, *expression));
}

void ast::EqualityExpression::addRightOperand(std::string oper, ast::RelationalExpression* expression){
    ast::EqualOp equalOp;
    if(oper == "==")
        equalOp = ast::EqualOp::Equal;
    else if(oper == "!=")
        equalOp = ast::EqualOp::NotEqual;
    _rightOperand.push_back(std::make_pair(equalOp, *expression));
}

void ast::AndExpression::addRightOperand(ast::EqualityExpression* expression){
    _rightOperand.push_back(std::make_pair(ast::AndOp::And, *expression));
}

void ast::Expression::addRightOperand(ast::AndExpression* expression){
    _rightOperand.push_back(std::make_pair(ast::OrOp::Or, *expression));
}