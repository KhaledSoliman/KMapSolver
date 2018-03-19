//
// Created by Mazen on 10.03.18.
//

#ifndef K_MAP_VARIABLE_H
#define K_MAP_VARIABLE_H

#include <string>

class Variable {
private:
    std::string name;
public:
    const std::string &getName() const;

    void setName(const std::string &name);
};


#endif //K_MAP_VARIABLE_H
