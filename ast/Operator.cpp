//
// Created by agata on 05.06.15.
//

#include "Operator.h"

std::string ast::toString(MultiplicativeOp o){
    switch (o){
        case MultiplicativeOp::Multiplicate:
            return "*";
        case MultiplicativeOp::Divide:
            return "/";
        case MultiplicativeOp::Modulo:
            return "%";
    }
}

std::string ast::toString(AdditiveOp o){
    switch (o){
        case AdditiveOp::Plus:
            return "+";
        case AdditiveOp::Minus:
            return "-";
    }
}

std::string ast::toString(RelationalOp o){
    switch(o){
        case RelationalOp::Less:
            return "<";
        case RelationalOp::More:
            return  ">";
        case RelationalOp::LessEqual:
            return "<=";
        case RelationalOp::MoreEqual:
            return ">=";
    }
}

std::string ast::toString(EqualOp o){
    switch(o){
        case EqualOp::Equal:
            return "==";
        case EqualOp::NotEqual:
            return "!=";
    }
}

std::string ast::toString(AndOp o){
    return "&&";
}

std::string ast::toString(OrOp o){
    return "||";
};

std::string ast::toString(AssignOp o){
    return "=";
}
