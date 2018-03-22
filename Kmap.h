//
// Created by Mazen & Khaled on 10.03.18
//

#ifndef K_MAP_KMAP_H
#define K_MAP_KMAP_H

#include <set>
#include <vector>
#include "Term.h"
#include "Variable.h"


class Kmap {
private:
    struct Rectangle {
        int width;

        int height;

        int getWidth() const {
            return width;
        }

        void setWidth(int width) {
            Rectangle::width = width;
        }

        int getHeight() const {
            return height;
        }

        void setHeight(int height) {
            Rectangle::height = height;
        }

        int calcArea() {
            return width * height;
        }
    };

    std::string extractVars(const std::string &expression) const;

    std::string extractMinterms(const std::string &expression) const;

    bool validateMinterms(const std::string &);

    Term **map;
    Variable *variableArray;
    std::string variables, minterms;
    std::set<int> mintermsSet;
    int numVariables, numMinterms, rowNum, columnNum;
public:
    Kmap() {};

    void generateMap(const std::string &);

    void validate(const std::string &);

    void fillMap();

    void printMap();

    void simplify();

    bool checkArray(int,int,int,int);

    std::string convertToExpression(int,int,int,int);

    void moveRect(int,int);

    std::string draw(int,std::vector<Term*>&);

    std::string getMinterms();
};


#endif //K_MAP_KMAP_H
