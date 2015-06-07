//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_TOKEN_H
#define LISTLANGUAGE_TOKEN_H

#include <string>

namespace ast {

    class Flag {
        std::string _name;
    public:
        Flag(std::string name) : _name(name) { };
    };

}

#endif //LISTLANGUAGE_TOKEN_H
