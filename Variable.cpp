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
    reset();
}

int Variable::getValue() const {
    return value;
}

void Variable::setValue(int value) {
    Variable::value = value;
}

int Variable::getChanged() const {
    return changed;
}

void Variable::setChanged(int changed) {
    Variable::changed = changed;
}

void Variable::reset() {
    changed = -1;
    value = -1;
}

