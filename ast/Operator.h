//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_OPERATOR_H
#define LISTLANGUAGE_OPERATOR_H

#include <string>

namespace ast {

    enum class MultiplicativeOp : int{
        Multiplicate,
        Divide,
        Modulo,
    };

    enum class AdditiveOp : int{
        Plus,
        Minus,
    };

    enum class RelationalOp : int{
        Less,
        More,
        LessEqual,
        MoreEqual,
    };

    enum class EqualOp : int{
        Equal,
        NotEqual,
    };

    enum class AndOp : int{
        And,
    };

    enum class OrOp : int{
        Or,
    };
    enum class AssignOp : int{
        Assign,
    };

    std::string toString(MultiplicativeOp o);
    std::string toString(AdditiveOp o);
    std::string toString(RelationalOp o);
    std::string toString(EqualOp o);
    std::string toString(AndOp o);
    std::string toString(OrOp o);
    std::string toString(AssignOp o);

}


#endif //LISTLANGUAGE_OPERATOR_H
