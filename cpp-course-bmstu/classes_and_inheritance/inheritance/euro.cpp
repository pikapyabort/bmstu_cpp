#include "euro.h"

double Euro::coef = 59.98;

Euro::Euro(double value) : Currency(value) {}

double Euro::toRuble() {
    return value * coef;
}

void Euro::print(std::ostream &out) const {
    out << value << "€";
}

void Euro::input(std::istream &in) {
    double tmp;
    in >> tmp;
    if (tmp < 0) throw WrongValueException("the sum is negative", tmp);
    value = tmp;
}

void Euro::setCoef(double newCoef){
    coef = newCoef;
}
