#include "fraction.h"

unsigned int Fraction::counter_frac = 0;

int gcd(int a, int b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

Fraction Fraction::simplify() {
    int g = abs(gcd(numerator, denominator));
    numerator /= g;
    denominator /= g;
    return *this;
}

Fraction Fraction::operator+(const Fraction &f) const {
    Fraction tmp{numerator * f.denominator + f.numerator * denominator,
                 static_cast<unsigned short>(denominator * f.denominator)};
    return tmp.simplify();
}

Fraction Fraction::operator-(const Fraction &f) const {
    return Fraction(numerator * f.denominator - f.numerator * denominator,
                    denominator * f.denominator).simplify();
}

Fraction Fraction::operator*(const Fraction &f) const {
    return Fraction(numerator * f.numerator,
                    denominator * f.denominator).simplify();
}

Fraction Fraction::operator/(const Fraction &f) const {
    if (f.numerator < 0)
        return Fraction(-numerator * f.denominator,
                        denominator * -f.numerator).simplify();
    return Fraction(numerator * f.denominator,
                    denominator * f.numerator).simplify();
}

Fraction Fraction::operator+(long num) const {
    return (*this + Fraction(num, 1)).simplify();
}

Fraction Fraction::operator-(long num) const {
    return (*this - Fraction(num, 1)).simplify();
}

Fraction Fraction::operator*(long num) const {
    return (*this * Fraction(num, 1)).simplify();
}

Fraction Fraction::operator/(long num) const {
    return (*this / Fraction(num, 1)).simplify();
}

bool Fraction::operator<(const Fraction &f) const {
    return numerator * f.denominator < f.numerator * denominator;
}

bool Fraction::operator>(const Fraction &f) const {
    return numerator * f.denominator > f.numerator * denominator;
}

bool Fraction::operator==(const Fraction &f) const {
    return numerator * f.denominator == f.numerator * denominator;
}

bool Fraction::operator!=(const Fraction &f) const {
    return numerator * f.denominator != f.numerator * denominator;
}

Fraction operator+(long num, const Fraction &f) {
    return  f + num;
}

Fraction operator-(long num, const Fraction &f) {
    return -(f-num);
}

Fraction operator*(long num, const Fraction &f) {
    return (Fraction(num, 1) * f).simplify();
}

Fraction operator/(long num, const Fraction &f) {
    return (Fraction(num, 1) / f).simplify();
}

std::ostream &operator<<(std::ostream &out, const Fraction &f) {
    if (f.denominator == 1)
        out << f.numerator;
    else
        out << f.numerator << "/" << f.denominator;
    return out;
}

std::istream &operator>>(std::istream &in, Fraction &f) {
    char slash = '0';
    std::cout << "Input fraction numerator and denominator separated by slash: " << std::endl;
    in >> f.numerator >> slash >> f.denominator;
    if (f.denominator == 0) {
        std::cout << "ERROR: ATTEMPTING TO DIVIDE BY ZERO" << std::endl;
        exit(0);
    }
    if (f.denominator < 0) {
        f.numerator *= -1;
        f.denominator *= -1;
    }
    f = f.simplify();
    return in;
}

Fraction::Fraction() : numerator(1), denominator(1) {
    ++counter_frac;
}

Fraction::Fraction(long n, unsigned short d) {
    if (d == 0) {
        std::cout << "ERROR: ATTEMPTING TO DIVIDE BY ZERO" << std::endl;
        exit(0);
    }
    numerator = n;
    denominator = d;
    ++counter_frac;
}

Fraction Fraction::operator-() const {
    return -1 * *this;
}

Fraction::Fraction(double p) {
    numerator = modf(p, &p);
    denominator = p;
    ++counter_frac;
}
