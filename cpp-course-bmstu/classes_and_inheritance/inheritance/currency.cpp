#include "exception.h"
#include "currency.h"

double Currency::toRuble() {
    return 0;
}

Currency::Currency(double newValue){
    if (newValue<0)
        throw WrongValueException("the sum is negative", newValue);
    value = newValue;
}

std::ostream &operator<<(std::ostream &out, const Currency &cur) {
    cur.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, Currency &cur) {
    cur.input(in);
    return in;
}

//Currency::Currency(const Currency &cur) = default; //!!! Это делается при объявлении. Это компилироваться вообще не должно
//исправила

//Currency::~Currency() = default; //!!! Это делается при объявлении. Это компилироваться вообще не должно
//исправила