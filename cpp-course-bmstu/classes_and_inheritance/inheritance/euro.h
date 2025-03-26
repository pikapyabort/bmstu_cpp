#ifndef INHERITANCE_EURO_H
#define INHERITANCE_EURO_H
#include "currency.h"

class Euro : public Currency {
    static double coef;
public:
    explicit Euro(double value = 0);
    double toRuble() override;
    void print(std::ostream &out) const override;
    void input(std::istream &in) override;
    static void setCoef(double newCoef);
};

#endif //INHERITANCE_EURO_H
