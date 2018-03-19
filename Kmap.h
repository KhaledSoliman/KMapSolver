//
// Created by Mazen on 10.03.18.
//

#ifndef K_MAP_KMAP_H
#define K_MAP_KMAP_H

#include "Term.h"
#include "Variable.h"
#include <iostream>
#include <string>


class Kmap {
private:
    Term** map;

public:
    Kmap();
    Kmap(Variable);
    Kmap(Variable, Variable);
    Kmap(Variable, Variable, Variable);
    Kmap(Variable, Variable, Variable, Variable);
    void validate(const std::string&);
    bool validateParenthesis(const std::string&);
    bool validateParenthesisExpressions(const std::string&);
    void generateMap(const std::string&);

    std::string getMinterms();
};



#endif //K_MAP_KMAP_H
