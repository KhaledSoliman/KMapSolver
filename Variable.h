//
// Created by Mazen & Khaled on 10.03.18.
//

#ifndef K_MAP_VARIABLE_H
#define K_MAP_VARIABLE_H

#include <string>

class Variable {
public:
    char getName() const;
    void setName(char name);
private:
    char name;
};


#endif //K_MAP_VARIABLE_H
