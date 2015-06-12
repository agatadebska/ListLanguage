//
// Created by agata on 10.06.15.
//

#ifndef LISTLANGUAGE_LITERAL_H
#define LISTLANGUAGE_LITERAL_H

#include <string>

namespace ast {

    class Literal {
        int* integer;
        float* floating;
    public:
        Literal(int _int) : integer(new int(_int)){}
        Literal(float _float) : floating(new float(_float)){}
      //  ~Literal();
    };

    bool isInteger(std::string& value);
    bool isFloat(std::string& value);
}


#endif //LISTLANGUAGE_LITERAL_H
