//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_EXPRESSION_H
#define LISTLANGUAGE_EXPRESSION_H

#include "Id.h"
#include "Operator.h"
#include <vector>
#include <utility>

namespace ast {

    struct Operand{
        ast::Id*    _id;
        int*        _int;
        float*      _float;
    };

    class MultiplicativeExpression{
        ast::Operand leftOperand;
        std::vector<std::pair<ast::MultiplicativeOp , ast::Operand>> _rightOperand;
    };

    class AdditiveExpression{
        ast::MultiplicativeExpression    _leftOperand;
        std::vector<std::pair<ast::AdditiveOp, ast::MultiplicativeExpression>> _rightOperand;
    };

    class RelationalExpression{
        ast::AdditiveExpression      _leftOperand;
        std::vector<std::pair<ast::RelationalOp, ast::AdditiveExpression>>  _rightOperand;
    };

    class EqualityExpression{
        ast::RelationalExpression    _leftOperand;
        std::vector<std::pair<ast::EqualOp , ast::RelationalExpression>>    _rightOperand;
    };

    class AndExpression{
        ast::EqualityExpression      _leftOperand;
        std::vector<std::pair<ast::AndOp , ast::EqualityExpression>>        _rightOperand;
    };

    class Expression {
        ast::AndExpression           _leftOperand;
        std::vector<std::pair<ast::OrOp, ast::AndExpression>>       _rightOperand;
    };












}


#endif //LISTLANGUAGE_EXPRESSION_H
