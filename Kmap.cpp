//
// Created by Mazen & Khaled on 10.03.18.
//

#include "Kmap.h"
#include <iostream>
#include <regex>
#include <cmath>


std::string Kmap::getMinterms() {
    std::string booleanExpression;
    std::cout << "Use this format to submit your boolean expression:" << std::endl;
    std::cout
            << "^\\s*[a-zA-Z]+\\s*\\((?!.*([a-zA-Z=]).*\\1)\\s*[a-zA-Z]\\s*(?:\\s*,\\s*[a-zA-Z]\\s*){1,3}\\)\\s*=\\s*\\(\\s*[[:digit:]]{1,2}\\s*(?:,\\s*[[:digit:]]{1,2}\\s*){0,15}\\)\\s*$"
            << std::endl;
    std::cout << "Example: F (a,b,c,d) = (0,1,2,3,5) " << std::endl;
    std::cout << "Please input your expression: ";
    std::getline(std::cin, booleanExpression);
    try {
        validate(booleanExpression);
        std::cout << "Format Accepted." << std::endl;
        std::cout << "Constructing K-Map" << std::endl;
        generateMap(booleanExpression);
    } catch (const std::string &e) {
        std::cout << e;
    };
}

void Kmap::generateMap(const std::string &expression) {
    rowNum = (numVariables == 3) ? 2 : numVariables;
    columnNum = (numVariables == 3) ? 4 : numVariables;

    map = new Term *[rowNum];
    for (int i = 0; i < rowNum; i++) {
        map[i] = new Term[columnNum];
    }
    fillMap();
    printMap();
    simplify();
}

void Kmap::validate(const std::string &expression) {
    std::regex format{
            "^\\s*[a-zA-Z]+\\s*\\((?!.*([a-zA-Z=]).*\\1)\\s*[a-zA-Z]\\s*(?:\\s*,\\s*[a-zA-Z]\\s*){1,3}\\)\\s*=\\s*\\(\\s*[[:digit:]]{1,2}\\s*(?:,\\s*[[:digit:]]{1,2}\\s*){0,15}\\)\\s*$"};
    std::string error = "Error: ";
    std::string invalidFormat = "Invalid boolean expression format, please revise your input.  ";
    std::string regexError = "[(1) expression does not match desired format]";
    std::string mintermsError = "[(2) number of minterms exceeds the maximum possible combinations of variables or minterms are not unique.]";

    if (!std::regex_match(expression, format)) {
        throw error + invalidFormat + regexError;
    } else if (!validateMinterms(expression)) {
        throw error + invalidFormat + mintermsError;
    }
}

bool Kmap::validateMinterms(const std::string &expression) {
    std::string variables = extractVars(expression);
    std::string minterms = extractMinterms(expression);
    std::set<int> mintermsSet;
    bool valid = true;
    int numVars = std::count(variables.begin(), variables.end(), ',') + 1;
    int numMinterms = std::count(minterms.begin(), minterms.end(), ',') + 1;
    std::string temp = std::string("");
    for (char a: minterms) {
        if (a == ',') {
            mintermsSet.insert(std::stoi(temp));
            temp = std::string("");
        } else if (isdigit(a)) {
            temp += a;
        }
    }
    mintermsSet.insert(std::stoi(temp));
    temp = "";
    Variable *variableArray = new Variable[numVars];
    int counter = 0;
    for (char a:variables) {
        if (isalpha(a)) {
            variableArray[counter++] = Variable(a);
        }
    }
    if (numMinterms > pow(2, numVars))
        valid = false;
    if (mintermsSet.size() != numMinterms)
        valid = false;

    if (valid) {
        this->variableArray = variableArray;
        this->numVariables = numVars;
        this->numMinterms = numMinterms;
        this->variables = variables;
        this->minterms = minterms;
        this->mintermsSet = mintermsSet;
    }
    return valid;
}

std::string Kmap::extractVars(const std::string &expression) const {
    return expression.substr(expression.find('(') + 1, expression.find(')') - expression.find('(') - 1);
}

std::string Kmap::extractMinterms(const std::string &expression) const {
    std::size_t posVars = expression.find(')') + 1;
    std::size_t posMinterms = expression.find('(', posVars) + 1;
    return expression.substr(posMinterms, expression.find(')', posVars) - posMinterms);
}

void Kmap::fillMap() {
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < columnNum; j++) {
            if (numVariables == 4) {
                std::bitset<2> X = (i == 2 ? std::bitset<2>(3) : (i == 3 ? std::bitset<2>(2) : std::bitset<2>(i)));
                std::bitset<2> Y = (j == 2 ? std::bitset<2>(3) : (j == 3 ? std::bitset<2>(2) : std::bitset<2>(j)));
                int num = std::bitset<4>(Y.to_string() + X.to_string()).to_ulong();
                bool val = !(mintermsSet.find(num) == mintermsSet.end());
                map[i][j].setX(X.to_string());
                map[i][j].setY(Y.to_string());
                map[i][j].setNumber(num);
                map[i][j].setValue(val);
            } else if (numVariables == 3) {
                std::bitset<1> X = std::bitset<1>(i);
                std::bitset<2> Y = (j == 2 ? std::bitset<2>(3) : (j == 3 ? std::bitset<2>(2) : std::bitset<2>(j)));
                int num = std::bitset<3>(Y.to_string() + X.to_string()).to_ulong();
                bool val = !(mintermsSet.find(num) == mintermsSet.end());
                map[i][j].setX(X.to_string());
                map[i][j].setY(Y.to_string());
                map[i][j].setNumber(num);
                map[i][j].setValue(val);
            } else {
                std::bitset<1> X = std::bitset<1>(i);
                std::bitset<1> Y = std::bitset<1>(j);
                int num = std::bitset<2>(Y.to_string() + X.to_string()).to_ulong();
                bool val = !(mintermsSet.find(num) == mintermsSet.end());
                map[i][j].setX(X.to_string());
                map[i][j].setY(Y.to_string());
                map[i][j].setNumber(num);
                map[i][j].setValue(val);
            }
            map[i][j].setPosx(i);
            map[i][j].setPosy(j);
        }
    }
}

void Kmap::printMap() {
    for (int j = 0; j < columnNum; j++) {
        if (j == 0) {
            for (int c = 0; c < numVariables; c++) {
                if (c == 2)
                    std::cout << '/';
                std::cout << variableArray[c].getName();
            }
        }
        std::cout << "    " << map[0][j].getY();
    }
    for (int i = 0; i < rowNum; i++) {
        std::cout << std::endl << map[i][0].getX();
        for (int j = 0; j < columnNum; j++) {
            std::cout << "    " << map[i][j].isTrue();
        }
    }
    std::cout << std::endl;
}


void Kmap::simplify() {
    std::string simplified;
    simplified += "F =";
    if (numMinterms == (rowNum * columnNum))
        simplified = "1";
    else if (numMinterms == 0)
        simplified == "0";
    else {
        bool first = true;
        int seen = 0;
        int possibilities = 8;
        int widths[] = {4, 2, 4, 1, 2, 2, 1, 1}; // 4x 2x 4x 1x 2x 2x 1x 1x
        int heights[] = {2, 4, 1, 4, 2, 1, 2, 1}; //2  4  1  4  2  1  2  1
        int p = 0;
        int width;
        int height;
        int area;
        while (p < possibilities && seen < numMinterms) {
            width = widths[p];
            height = heights[p];
            area = width * height;
            for (int i = 0; i < rowNum; i++) {
                for (int j = 0; j < columnNum; j++) {
                    if (checkArray(i, j, width, height)) {
                        simplified += first ? " " : " + ";
                        simplified += convertToExpression(i, j, width, height);
                        seen += area;
                        first = false;
                    }
                }
            }
            p++;
        }
    }
    std::cout << simplified << std::endl;
}

bool Kmap::checkArray(int x0, int y0, int xM, int yM) {
    //if rect width or height violates possible arrays from current map return false
    if (y0 + yM <= (columnNum + 1) && x0 + xM <= (rowNum + 1)) {
        bool flag = true;
        int x;
        int y;
        int seen = 0;
        for (int i = x0; i < x0 + xM; i++) {
            x = i == rowNum ? 0 : i;
            for (int j = y0; j < y0 + yM; j++) {
                y = j == columnNum ? 0 : j;
                //std::cout << x << ", " << y << std::endl;
                if (!map[x][y].isTrue()) {
                    flag = false;
                    goto endloop;
                } else if (map[x][y].isSeen())
                    seen++;
            }
        }
        //if all terms were seen by another rect return false
        if (seen >= (xM * yM))
            flag = false;
        endloop:
        return flag;
    } else {
        return false;
    }
}

std::string Kmap::convertToExpression(int x0, int y0, int xM, int yM) {
    std::string exp;
    char comp = '\'';
    int x;
    int y;
    int xNext;
    int yNext;
    std::string binary;
    std::string binary2;
    for (int i = x0; i < x0 + xM; i++) {
        x = i == rowNum ? 0 : i;
        for (int j = y0; j < y0 + yM; j++) {
            y = j == columnNum ? 0 : j;
            map[x][y].setSeen(true);
        }
    }
    if (yM == 2) {
        for (int j = y0; j < y0 + yM; j += 2) {
            y = j == columnNum ? 0 : j;
            yNext = (y + 1) > columnNum - 1 ? 0 : y + 1;
            binary = map[x0][y].getY();
            binary2 = map[x0][yNext].getY();
            for (int c = 0; c < binary.size(); c++) {
                if (binary2[c] == binary[c]){
                    exp += variableArray[c].getName();
                    if(binary[c] == '0')
                        exp += comp;
                }
            }
        }
    } else if (yM == 1) {
        binary = map[x0][y0].getY();
        for (int c = 0; c < binary.size(); c++) {
            exp += variableArray[c].getName();
            if(binary[c] == '0')
                exp += comp;
        }
    }
    if (xM == 2) {
        for (int i = x0; i < x0 + xM; i += 2) {
            x = i == rowNum ? 0 : i;
            xNext = (x + 1) > rowNum - 1 ? 0 : x + 1;
            binary = map[x][y0].getX();
            binary2 = map[xNext][y0].getX();
            for (int c = 0; c < binary.size(); c++) {
                if (binary2[c] == binary[c]){
                    exp += variableArray[(int)ceil(numVariables / 2.0) + c].getName();
                    if(binary[c] == '0')
                        exp += comp;
                }
            }
        }
    } else if (xM == 1) {
        binary = map[x0][y0].getX();
        for (int c = 0; c < binary.size(); c++) {
            exp += variableArray[(int)ceil(numVariables / 2.0) + c].getName();
            if(binary[c] == '0')
                exp += comp;
        }
    }

    return exp;
}


