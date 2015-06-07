//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_RETURNSTATEMENT_H
#define LISTLANGUAGE_RETURNSTATEMENT_H

#include "Id.h"

namespace ast {

    class ReturnStatement {
        ast::Id*       _id;
        int*           _int;
        float*         _float;
    };
}


#endif //LISTLANGUAGE_RETURNSTATEMENT_H
