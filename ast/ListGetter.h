//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_LISTGETTER_H
#define LISTLANGUAGE_LISTGETTER_H

#include "Id.h"

namespace ast {

    class ListGetter {
        ast::Id _id;
        int     _index;
    public:
        ListGetter(){}
      //  ~ListGetter(){};
        ListGetter(ast::Id& id, int& index) : _id(id), _index(index){};
    };
}


#endif //LISTLANGUAGE_LISTGETTER_H
