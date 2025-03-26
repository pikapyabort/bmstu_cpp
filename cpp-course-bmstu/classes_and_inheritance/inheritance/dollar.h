#ifndef INHERITANCE_DOLLAR_H
#define INHERITANCE_DOLLAR_H
#include "currency.h"

class Dollar : public Currency {
    static double coef;
public:
    explicit Dollar(double value = 0);
    double toRuble() override;
    void print(std::ostream &out) const override;
    void input(std::istream &in) override;
    static void setCoef(double newCoef);
};

#endif //INHERITANCE_DOLLAR_H
