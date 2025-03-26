#pragma once
#include "Vector.h"
#include <iomanip>
#include "exception.h"

class CSRMatrix{
    //values
    double *m_aelem;
    //pointer to column for aelem
    int *m_jptr;
    //number of elements in rows
    int *m_iptr;
    // number of non-null values – size of aelem/jptr
    int m_jsize;
    //dimension (n)
    int m_dim;

public:
    CSRMatrix();
    CSRMatrix(double *p_aelem, int *p_jptr, int *p_iptr, int p_jsize = 0, int p_dim = 0);
    CSRMatrix(const CSRMatrix &matrix);

    CSRMatrix operator*(const double alpha);
    Vector operator*(const Vector& vector) const;


    int getNumberOfValues() const;
    int getDimention() const;

    ~CSRMatrix();

    friend Vector operator*(const Vector& vector, const CSRMatrix &matrix);

    friend CSRMatrix operator*(const double alpha, const CSRMatrix& matrix);
    friend Vector operator*(const Vector &vector, const CSRMatrix &matrix);
    friend std::istream& operator>>(std::istream& in, CSRMatrix& matrix);
    friend std::ostream& operator<<(std::ostream& out, const CSRMatrix& matrix);

};