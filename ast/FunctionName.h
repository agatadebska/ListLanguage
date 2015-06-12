//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_FUNCTIONNAME_H
#define LISTLANGUAGE_FUNCTIONNAME_H

#include <string>

namespace ast {

    enum class FunctionName : int{
        Map,
        Filter,
        Merge,
        Length,
        Print,
    };

    ast::FunctionName functionNameFromString(std::string&);
}


#endif //LISTLANGUAGE_FUNCTIONNAME_H
