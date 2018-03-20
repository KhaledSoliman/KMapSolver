//
// Created by Mazen & Khaled on 10.03.18
//

#ifndef K_MAP_KMAP_H
#define K_MAP_KMAP_H

#include "Term.h"
#include "Variable.h"


class Kmap {
public:
    Kmap();

    Kmap(Variable, Variable);

    Kmap(Variable, Variable, Variable);

    Kmap(Variable, Variable, Variable, Variable);

    void generateMap(const std::string &);

    void validate(const std::string &) const;

    std::string getMinterms();

private:
    std::string extractVars(const std::string &expression) const;

    std::string extractMinterms(const std::string &expression) const;

    bool validateMinterms(const std::string &) const;

    Term **map;
};


#endif //K_MAP_KMAP_H
