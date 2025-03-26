#include "dollar.h"

double Dollar::coef = 60.28;

Dollar::Dollar(double newValue) : Currency(newValue) {}

double Dollar::toRuble() {
    return value * coef;
}

void Dollar::print(std::ostream &out) const {
    out << value << "$";
}

void Dollar::input(std::istream &in) {
    double tmp;
    in >> tmp;
    if (tmp < 0) throw WrongValueException("the sum is negative", tmp);
    value = tmp;
}

void Dollar::setCoef(double newCoef){
    coef = newCoef;
}

