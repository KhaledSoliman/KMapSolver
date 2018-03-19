//
// Created by Mazen on 10.03.18.
//

#include "Variable.h"

const std::string &Variable::getName() const {
    return name;
}

void Variable::setName(const std::string &name) {
    Variable::name = name;
}
