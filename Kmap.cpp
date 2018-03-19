//
// Created by Mazen on 10.03.18.
//

#include "Kmap.h"
#include <algorithm>
#include <set>
#include <iostream>

Kmap::Kmap(Variable v1, Variable v2) {
    map = new Term*[2];
    for(int i=0; i<2; i++) {
        map = new Term*[2];
    }
}

Kmap::Kmap(Variable, Variable, Variable) {
    map = new Term*[4];
    for(int i=0; i<4; i++) {
        map = new Term*[2];
    }
}

Kmap::Kmap(Variable, Variable, Variable, Variable) {
    map = new Term*[4];
    for(int i=0; i<4; i++) {
        map = new Term*[4];
    }
}

std::string Kmap::getMinterms() {
    std::string booleanExpression;
    std::cout << "Enter Function Boolean Expression in the format F(Var#1,Var#2,Var#3,Var#4) = (0,5,6) ";
    std::cin >> booleanExpression;
    try{
        validate(booleanExpression);
        std::cout << "Format Accepted." << std::endl;
        std::cout << "Constructing K-Map" << std::endl;
        generateMap(booleanExpression);
    } catch(const std::invalid_argument& e){
        std::cout << e.what();
    };
}

void Kmap::generateMap(const std::string& expression){

}

void Kmap::validate(const std::string& expression){
    std::string error = "Error: ";
    std::string invalidFormat = "Invalid boolean expression format.  ";
    std::string parenthesisError = "(1::Check Parenthesis Format Order/Number)";
    std::string parenthesisError2 = "(2::Check Parenthesis Format Variables/Minterms || Name (vars) = (minterms) is not satisfied)";
    if( validateParenthesis(expression) ){
        throw std::invalid_argument(error + invalidFormat + parenthesisError);
    }else if( validateParenthesisExpressions(expression)){
        throw std::invalid_argument(error + invalidFormat + parenthesisError2);
    }
}

/* Deprected Functions
bool validateNumParenthesis(const std::string& expression){
    int openedP = std::count(expression.begin(), expression.end(), '(');
    int closedP = std::count(expression.begin(), expression.end(), ')');

    return (openedP != 2 || closedP != 2);
}
*/

//Better Functions
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


