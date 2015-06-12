//
// Created by agata on 05.06.15.
//

#ifndef LISTLANGUAGE_RANGE_H
#define LISTLANGUAGE_RANGE_H

namespace ast {

    class Range {
        int start;
        int end = -1;
    public:
        Range(){}
        Range(int _start, int _end) : start(_start), end(_end){};
        Range(int _start) : start(_start){};
    };
}


#endif //LISTLANGUAGE_RANGE_H
