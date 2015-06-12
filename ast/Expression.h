//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_EXPRESSION_H
#define LISTLANGUAGE_EXPRESSION_H

#include "Id.h"
#include "Operator.h"
#include "../parser/scanner/scanner.h"
#include <vector>
#include <utility>
#include <memory>

namespace ast {

    struct Operand{
        ast::Id* _id = nullptr;
        int*  _int = nullptr;
        float*  _float = nullptr;

        Operand(){};
        Operand(std::string& val);
     //   ~Operand();
        bool isGood();
        Operand(const Operand&);
    };

    class MultiplicativeExpression{
        ast::Operand _leftOperand;
        std::vector<std::pair<ast::MultiplicativeOp , ast::Operand>> _rightOperand;

    public:
        MultiplicativeExpression(){}
        MultiplicativeExpression(std::string& val) : _leftOperand(val){};
        void addRightOperand(std::string oper, std::string val);
        bool isGood();
    };

    class AdditiveExpression{
        ast::MultiplicativeExpression    _leftOperand;
        std::vector<std::pair<ast::AdditiveOp, ast::MultiplicativeExpression>> _rightOperand;
    public:
        AdditiveExpression(){}
        AdditiveExpression(ast::MultiplicativeExpression& expression) : _leftOperand(expression){};
        void addRightOperand(std::string, ast::MultiplicativeExpression*);
        bool isGood();
    };

    class RelationalExpression{
        ast::AdditiveExpression      _leftOperand;
        std::vector<std::pair<ast::RelationalOp, ast::AdditiveExpression>>  _rightOperand;
    public:
        RelationalExpression(){}
        RelationalExpression(ast::AdditiveExpression& expression) : _leftOperand(expression){};
        void addRightOperand(std::string, ast::AdditiveExpression*);
        bool isGood();
    };

    class EqualityExpression{
        ast::RelationalExpression    _leftOperand;
        std::vector<std::pair<ast::EqualOp , ast::RelationalExpression>>    _rightOperand;
    public:
        EqualityExpression(){}
        EqualityExpression(ast::RelationalExpression& expression) : _leftOperand(expression){};
        void addRightOperand(std::string, ast::RelationalExpression*);
        bool isGood();
    };

    class AndExpression{
        ast::EqualityExpression      _leftOperand;
        std::vector<std::pair<ast::AndOp , ast::EqualityExpression>>        _rightOperand;
    public:
        AndExpression(){}
        AndExpression(ast::EqualityExpression& expression) : _leftOperand(expression){};
        void addRightOperand(ast::EqualityExpression* expression);
        bool isGood();
    };

    class Expression {
        ast::AndExpression           _leftOperand;
        std::vector<std::pair<ast::OrOp, ast::AndExpression>>       _rightOperand;
    public:
        Expression(){}
        ~Expression(){}
        Expression(ast::AndExpression& expression) : _leftOperand(expression){};
        void addRightOperand(ast::AndExpression* expression);
        bool isGood();
    };












}


#endif //LISTLANGUAGE_EXPRESSION_H
