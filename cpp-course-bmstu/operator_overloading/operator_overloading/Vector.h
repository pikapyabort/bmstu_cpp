#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "exception.h"

class CSRMatrix;

class Vector {
    int m_dim;
    double *m_pointer;
public:
    //constructors
    Vector(int n, double *pointer);
    Vector(int n, double value = 0);
    Vector(const Vector &vector);

    //destructor
    ~Vector();

   //operator overloading
    Vector &operator=(const Vector &vector);
    Vector &operator+=(const Vector &vector);
    Vector &operator-=(const Vector &vector);
    Vector operator+(const Vector &vector);
    Vector operator-(const Vector &vector);
    Vector &operator+();
    Vector operator-();
    double operator*(const Vector &vector) const;
    Vector operator*(double alpha) const;
    const double &operator[](int i) const;
    double& operator[](int i);

    friend Vector operator*(double alpha, const Vector &vector);
    friend Vector operator+(const Vector &vector1, const Vector &vector2);
    friend Vector operator-(const Vector &vector1, const Vector &vector2);
    friend std::ostream &operator<<(std::ostream &out, const Vector &vec);
    friend std::istream &operator>>(std::istream &in, Vector &vec);

    //cast
    explicit operator double() const;

    //methods
    double getLength() const;
    int getDim() const;
};
Vector operator*(double alpha, const Vector &vector);