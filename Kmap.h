//
// Created by Mazen on 10.03.18.
//

#ifndef K_MAP_KMAP_H
#define K_MAP_KMAP_H

#include "Term.h"
#include "Variable.h"
#include <iostream>


class Kmap {
private:
    Term** map;

public:
    Kmap();
    Kmap(Variable);
    Kmap(Variable, Variable);
    Kmap(Variable, Variable, Variable);
    Kmap(Variable, Variable, Variable, Variable);

    std::string getMinterms()
};



#endif //K_MAP_KMAP_H
