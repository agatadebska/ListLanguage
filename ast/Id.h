//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_ID_H
#define LISTLANGUAGE_ID_H

#include <string>

namespace ast {

    class Id {
        std::string _id;
    public:
        Id(){};
        Id(std::string i) : _id(i){}
    };

}


#endif //LISTLANGUAGE_ID_H
