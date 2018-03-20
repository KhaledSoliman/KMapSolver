//
// Created by Mazen & Khaled on 10.03.18.
//

#include "Kmap.h"
#include <iostream>
#include <regex>
#include <cmath>

Kmap::Kmap(Variable v1, Variable v2) {
    map = new Term *[2];
    for (int i = 0; i < 2; i++) {
        map[i] = new Term [2];
    }
}

Kmap::Kmap(Variable v1, Variable v2, Variable v3) {
    map = new Term *[4];
    for (int i = 0; i < 4; i++) {
        map[i] = new Term [2];
    }
}

Kmap::Kmap(Variable v1, Variable v2, Variable v3, Variable v4) {
    map = new Term *[4];
    for (int i = 0; i < 4; i++) {
        map[i] = new Term [4];
    }
}

std::string Kmap::getMinterms() {
    std::string booleanExpression;
    std::cout << "Use this format to submit your boolean expression:" << std::endl;
    std::cout << "^[a-zA-Z]+\\s*\\((?!.*([a-zA-Z0-9=]).*\\1)[a-zA-Z](?:,[a-zA-Z]){1,3}\\)\\s*=\\s*\\([0-9](?:,[0-9]){0,15}\\)\\s*$" << std::endl;
    std::cout << "Example: F (a,b,c,d) = (0,1,2,3,5) " << std::endl;
    std::cout << "Please input your expression: ";
    std::cin >> booleanExpression;
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
    this->variables = extractVars(expression);
    this->minterms = extractMinterms(expression);

}

void Kmap::validate(const std::string &expression) const {
    std::regex format = std::regex(
            "^[a-zA-Z]+\\s*\\((?!.*([a-zA-Z0-9=]).*\\1)[a-zA-Z](?:,[a-zA-Z]){1,3}\\)\\s*=\\s*\\([0-9](?:,[0-9]){0,15}\\)\\s*$");
    std::string error = "Error: ";
    std::string invalidFormat = "Invalid boolean expression format, please revise your input.  ";
    std::string regexError = "[(1) expression does not match desired format]";
    std::string mintermsError = "[(2) number of minterms exceeds the maximum possible combinations of variables]";

    if (!std::regex_match(expression, format)) {
        throw error + invalidFormat + regexError;
    } else if (!validateMinterms(expression)) {
        throw error + invalidFormat + mintermsError;
    }
}

bool Kmap::validateMinterms(const std::string &expression) const {
    std::string variables = extractVars(expression);
    std::string minterms= extractMinterms(expression);
    bool valid = true;
    int numVars = 0;
    int numMinterms = 0;

    for (char a : variables)
        if (a != ',' && a != ' ')
            numVars += 1;
    for (char a: minterms)
        if (a != ',' && a != ' ')
            numMinterms += 1;
    if (numMinterms > pow(2, numVars))
        valid = false;

    if(valid) {
        this->variables = variables;
        this->minterms = minterms;
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

void Kmap::fillKmap() {

}


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


