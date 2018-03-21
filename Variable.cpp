//
// Created by Mazen & Khaled on 10.03.18.
//

#include "Variable.h"

char Variable::getName() const {
    return name;
}

void Variable::setName(char name) {
    this->name = name;
}

Variable::Variable(char name)  {
    this->name=name;
}

