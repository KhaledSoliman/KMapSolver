//
// Created by Mazen on 10.03.18.
//

#include "Kmap.h"


Kmap::Kmap(Variable v1, Variable v2) {
    map = new Term*[2];
    for(int i=0; i<2; i++) {
        map = new Term*[2];
    }
}

Kmap::Kmap(Variable, Variable, Variable) {
    map = new Term*[4];
    for(int i=0; i<4; i++) {
        map = new Term*[2];
    }
}

Kmap::Kmap(Variable, Variable, Variable, Variable) {
    map = new Term*[4];
    for(int i=0; i<4; i++) {
        map = new Term*[4];
    }
}

std::string Kmap::getMinterms() {
    int min;
    std::cout<<"Enter minterm :";
    std::cin>>min;

    return std::string();
}
