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
}

void Kmap::simplify() {
    Rectangle rect;
    std::vector<Term> block;
    std::string simplifiedExpression;
    Term nextTerm;
    Term term;
    int difference = 0;
    int numSeen = 0;

    for(int i =0; i<rowNum; i++) {
        for (int j = 0; j < columnNum; j++) {
            if(map[i][j].isTrue() && !map[i][j].isSeen()){
                term = map[i][j];
                term.setSeen(true);
                block.push_back(term);
                while(numSeen < numMinterms) {
                    //Go Right
                    difference = std::stoi(term.getY()) == (columnNum - 1) ? -columnNum + 1 : 1;
                    nextTerm = map[std::stoi(term.getX())][std::stoi(term.getY()) + difference];
                    while(nextTerm.isTrue()&& !nextTerm.isSeen()){
                        nextTerm.setSeen(true);
                        block.push_back(nextTerm);
                        difference = std::stoi(term.getY()) == (columnNum - 1) ? -columnNum + 1 : 1;
                        nextTerm = map[std::stoi(term.getX())][std::stoi(term.getY()) + difference];
                    }
                    //Go Left
                    difference = std::stoi(term.getY()) == 0 ? columnNum - 1 : -1;
                    nextTerm = map[std::stoi(term.getX())][std::stoi(term.getY()) + difference];
                    while(nextTerm.isTrue()&& !nextTerm.isSeen()){
                        nextTerm.setSeen(true);
                        block.push_back(nextTerm);
                        difference = std::stoi(term.getY()) == 0 ? columnNum - 1 : -1;
                        nextTerm = map[std::stoi(term.getX())][std::stoi(term.getY()) + difference];
                    }
                    //Go Down
                    difference = std::stoi(term.getX()) == (rowNum - 1) ? -rowNum + 1 : 1;
                    nextTerm = map[std::stoi(term.getX()) + difference][std::stoi(term.getY())];
                    while(nextTerm.isTrue()&& !nextTerm.isSeen()){
                        nextTerm.setSeen(true);
                        block.push_back(nextTerm);
                        difference = std::stoi(term.getY()) == 0 ? columnNum - 1 : -1;
                        nextTerm = map[std::stoi(term.getX())][std::stoi(term.getY()) + difference];
                    }
                    //Go Up
                    difference = std::stoi(term.getX()) == 0 ? rowNum - 1 : -1;
                    nextTerm = map[std::stoi(term.getX()) + difference][std::stoi(term.getY())];
                    while(nextTerm.isTrue()&& !nextTerm.isSeen()){
                        nextTerm.setSeen(true);
                        block.push_back(nextTerm);
                        difference = std::stoi(term.getY()) == 0 ? columnNum - 1 : -1;
                        nextTerm = map[std::stoi(term.getX())][std::stoi(term.getY()) + difference];
                    }

                    for(Term a: block){
                        std::cout << a.getNumber() << " ";
                    }
                    std::cout << std::endl;
                    block.clear();
                }
            }
        }
    }



    /*
    if (numVariables == 4 && numMinterms == 16) {
        simplifiedExpression = "1";
    }
    if (numVariables <= 4 && numVariables >= 3 && numMinterms >= 8) {
        rect.setHeight(4);
        rect.setWidth(2);
        simplifiedExpression += draw(rect);
    }
    if (numMinterms >= 2) {
        rect.setHeight(2);
        rect.setWidth(2);
        simplifiedExpression += draw(rect);
    }
    if (numMinterms >= 1) {
        rect.setHeight(1);
        rect.setWidth(1);
        simplifiedExpression += draw(rect);
    } else {
        simplifiedExpression = "0";
    }
    */

}

std::string Kmap::draw(Rectangle rect) {
    int i = 0;
    int area = rect.calcArea();
    while(i < rowNum){
        int j = 0;
        while( j < columnNum){

        }
    }
}
/*
void Kmap::getContigousBlock(std::vector<Term>& block, Term& term){

}

*/
/* Deprecated Functions
bool validateNumParenthesis(const std::string& expression){
    int openedP = std::count(expression.begin(), expression.end(), '(');
    int closedP = std::count(expression.begin(), expression.end(), ')');

    return (openedP != 2 || closedP != 2);
}
bool Kmap::validateParenthesis(const std::string& expression){
    std::string m;
    for(char a: expression){
        if(a == '(' || a==')'){
            m += a;
        }
    }
    return !(m == "()()");
}

bool Kmap::validateParenthesisExpressions(const std::string& expression){
    std::string vars = expression.substr(expression.find('(')+1, expression.find(')')-expression.find('(')-1);
    std::size_t pepe = expression.find(vars);
    std::size_t cece = expression.find('(',pepe+vars.length()+1)+1;
    std::string minterms = expression.substr(cece,expression.find(')',pepe+vars.length()+1)-cece);
    std::string equalSign = expression.substr(pepe+vars.length()+1,cece-(pepe+vars.length()+1));
    std::string functionName = expression.substr(0,pepe-1);
    std::string v;
    std::string m;
    bool invalid = false;


    //Check 1
    for(char a: vars){
        if(!isalpha(a) && a != ',' && a != ' '){
            invalid = true;
        }else if(a != ' '){
            v += a;
        }
    }
    for(char a: minterms){
        if(!isdigit(a) && a != ',' && a != ' '){
            invalid = true;
        }else if(a != ' '){
            m += a;
        }
    }
    for(char a: functionName){
        if(!isalpha(a) || a != ' ')
            invalid = true;
    }

    //Check 2
    if(v[0] == ',' || v[v.length()-1] == ',' || m[0] == ',' || m[m.length()-1] == ','){
        invalid = true;
    }else if(v.length() <= 2 || m.length() == 0){
        invalid = true;
    }else {
        int numVars = 0;
        int numMinterms = 0;
        for(char a : v){
            if(a != ',')
                numVars+=1;
        }
        for(char a: m){
            if(a != ',')
                numMinterms+=1;
        }
        if(numVars > 4 || numVars < 2)
            invalid = true;
        else if(numMinterms > pow(2,numVars))
            invalid = true;
        for(unsigned int i = 1; i < v.length()-1; i++){
            if(v[i] == ',' && v[i+1] == ','){
                invalid = true;
            }
        }
        for(unsigned int i = 1; i < m.length()-1; i++){
            if(m[i] == ',' && m[i+1] == ',' ){
                invalid = true;
            }
        }
        equalSign.erase(std::remove_if(equalSign.begin(), equalSign.end(), isspace), equalSign.end());
        std::set<char> checkerV(v.begin(), v.end());
        std::set<char> checkerM(m.begin(), m.end());
        if (checkerV.size() != (v.size()-std::count(v.begin(),v.end(),',')+1) || checkerM.size() != (m.size()-std::count(m.begin(),m.end(),',')+1) || equalSign != "=")
            invalid = true;
    }

    return invalid;
}
*/


