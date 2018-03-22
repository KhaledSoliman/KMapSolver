//
// Created by Mazen & Khaled on 10.03.18.
//

#ifndef K_MAP_TERM_H
#define K_MAP_TERM_H


#include <bitset>

class Term {
private:
    bool value;
    int posx;
    int number;
    bool inluded;
    int posy;
    bool seen;
    std::string X;
    std::string Y;
public:
    int getPosx() const;

    void setPosx(int posx);

    int getPosy() const;

    void setPosy(int posy);

    bool isInluded() const;

    void setInluded(bool inluded);

    const std::string &getX() const;

    void setX(const std::string &X);

    const std::string &getY() const;

    void setY(const std::string &Y);

    bool isSeen() const;

    void setSeen(bool seen);

    Term():seen(false){}
    int getNumber() const;

    void setNumber(int number);

    bool setValue(bool);
    bool isTrue() const;
};


#endif //K_MAP_TERM_H
