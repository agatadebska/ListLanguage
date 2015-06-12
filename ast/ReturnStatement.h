//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_RETURNSTATEMENT_H
#define LISTLANGUAGE_RETURNSTATEMENT_H

#include "Id.h"
#include "Literal.h"

namespace ast {

    class ReturnStatement {
        ast::Id*       _id = nullptr;
        ast::Literal*    _literal = nullptr;

    public:
        ReturnStatement(){}
     //   ~ReturnStatement();
        ReturnStatement(std::string& val);
    };


}


#endif //LISTLANGUAGE_RETURNSTATEMENT_H
