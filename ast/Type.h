//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_TYPE_H
#define LISTLANGUAGE_TYPE_H

#include <string>

namespace ast {

    enum class Type : int {
        Int,
        Float,
    };

    std::string toString(Type t);
}


#endif //LISTLANGUAGE_TYPE_H
