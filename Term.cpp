//
// Created by Mazen on 10.03.18.
//

#include "Term.h"

bool Term::isTrue() const {
    return value;
}

bool Term::setValue(bool value) {
    this->value = value;
}

int Term::getNumber() const {
    return number;
}

void Term::setNumber(int number) {
    Term::number = number;
}

bool Term::isSeen() const {
    return seen;
}

void Term::setSeen(bool seen) {
    Term::seen = seen;
}

const std::string &Term::getX() const {
    return X;
}

void Term::setX(const std::string &X) {
    Term::X = X;
}

const std::string &Term::getY() const {
    return Y;
}

void Term::setY(const std::string &Y) {
    Term::Y = Y;
}

