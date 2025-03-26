#ifndef INHERITANCE_CURRENCY_H
#define INHERITANCE_CURRENCY_H
#include <iostream>
#include "exception.h"

class Currency {
protected:
    double value;
public:
    explicit Currency(double newValue = 0);
    
    //!!! Конструктор и без default предоставляется
    //убрала
   // Currency(const Currency& cur) = default;

    virtual ~Currency() = default;

    virtual double toRuble() = 0;
    virtual void print(std::ostream &out) const = 0;
    virtual void input(std::istream &in) = 0;

    friend std::ostream &operator<<(std::ostream &out, const Currency& cur);
    friend std::istream &operator>>(std::istream &in, Currency& cur);
};

#endif