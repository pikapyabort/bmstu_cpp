//#ifndef CLASSES_AND_INHERITANCE_FRACTION_H
//#define CLASSES_AND_INHERITANCE_FRACTION_H
//
//#endif //CLASSES_AND_INHERITANCE_FRACTION_H
#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cfenv>

using std::cout;
using std::cin;
using std::endl;

class Fraction {
    long numerator;
    unsigned short denominator;
    static unsigned int counter_frac;
public:
    Fraction();
    Fraction(long n, unsigned short d);
    Fraction(double p);

    Fraction operator-() const;
    Fraction operator+(const Fraction &f) const;
    Fraction operator-(const Fraction &f) const;
    Fraction operator*(const Fraction &f) const;
    Fraction operator/(const Fraction &f) const;

    bool operator<(const Fraction &f) const;
    bool operator>(const Fraction &f) const;
    bool operator==(const Fraction &f) const;
    bool operator!=(const Fraction &f) const;

    Fraction operator+(long num) const;
    Fraction operator-(long num) const;
    Fraction operator*(long num) const;
    Fraction operator/(long num) const;


    long getNum() const{
        return numerator;
    }


    unsigned short getDen() const{
        return denominator;
    }

    static unsigned int getCounter(){
        std::cout << "Fraction objects were created:" << counter_frac << std::endl;
        return counter_frac;
    }

    double toDouble() const{
        return double(numerator) / double(denominator);
    }

    Fraction simplify();
    friend std::ostream &operator<<(std::ostream &out, const Fraction& f);
    friend std::istream &operator>>(std::istream &in, Fraction& f);
};

Fraction operator+(long num, const Fraction &f);
Fraction operator-(long num, const Fraction &f);
Fraction operator*(long num, const Fraction &f);
Fraction operator/(long num, const Fraction &f);

