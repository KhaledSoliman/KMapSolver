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
