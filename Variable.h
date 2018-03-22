//
// Created by Mazen & Khaled on 10.03.18.
//

#ifndef K_MAP_VARIABLE_H
#define K_MAP_VARIABLE_H

#include <string>

class Variable {
public:
    Variable() {reset();};

    Variable(char);

    char getName() const;

    void reset();

    void setName(char);

    int getValue() const;

    void setValue(int value);

    int getChanged() const;

    void setChanged(int changed);

private:
    int value;
    int changed;
    char name;
};


#endif //K_MAP_VARIABLE_H
