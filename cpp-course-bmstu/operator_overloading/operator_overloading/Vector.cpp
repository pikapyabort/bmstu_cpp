#include "Vector.h"

//fill with default number
Vector::Vector(int n, double value) : m_dim(n) {
    if (n > 0) {
        m_pointer = new double[n];
        for (int i = 0; i < n; i++)
            m_pointer[i] = value;
    }
}

//copy of array
Vector::Vector(int n, double arr[]): m_dim(n){
    m_pointer = new double[n];
    for (int i = 0; i < n; i++)
        m_pointer[i] = arr[i];
}

//copy of another vector
Vector::Vector(const Vector &vector) : m_dim(vector.m_dim){
    if (m_dim > 0){
        m_pointer = new double[m_dim];
        for (int i = 0; i < m_dim; i++) {
            m_pointer[i] = vector.m_pointer[i];
        }
    }
    else
        m_pointer = nullptr;
}

//destructor
Vector::~Vector() {
    delete[] m_pointer;
}

//operators!

const double& Vector::operator[](int i) const{ //!!! Если это версия для чтения, то нужен const у возвращаемого типа. (Не исправлено)
                                                //fixed
    if (i > m_dim)
        throw OutOfRangeException();
    else
        return m_pointer[i];
}

double& Vector::operator[](int i){ //версия для записи
    if (i > m_dim)
        throw OutOfRangeException();
    else
        return m_pointer[i];
}

Vector& Vector::operator=(const Vector &vector){
    if (&vector == this){
        return *this;
    }

    if (vector.m_dim != m_dim) {
        delete[] m_pointer;
        m_pointer = new double[vector.m_dim]; //!!! Лишний this (не исправлено) - исправила
        m_dim = vector.m_dim; //!!! Лишний this (не исправлено) - исправила
    }

    for (int i = 0; i < m_dim; i++)
        m_pointer[i] = vector.m_pointer[i]; //!!! Лишний this (не исправлено) - исправила

    return *this;
}

Vector& Vector::operator+=(const Vector &vector){
    if (vector.m_dim != m_dim)
        throw OutOfRangeException();
    else {
        for (int i = 0; i < m_dim; i++)
            m_pointer[i] += vector.m_pointer[i];
    }
    return (*this);
}

Vector& Vector::operator-=(const Vector &vector){
    if (vector.m_dim != m_dim)
        throw OutOfRangeException();
    else {
        for (int i = 0; i < m_dim; i++)
            m_pointer[i] -= vector.m_pointer[i];
    }
    return (*this);
}

Vector Vector::operator+(const Vector& vector){
    if (m_dim != vector.m_dim)
        throw OutOfRangeException();
    Vector tmp(m_dim);
    for (int i = 0; i < tmp.m_dim; i++) {
        tmp.m_pointer[i] = m_pointer[i] + vector.m_pointer[i];
    }
    return tmp;
}

Vector Vector::operator-(const Vector& vector){
    if (m_dim != vector.m_dim)
        throw OutOfRangeException();
    Vector tmp(m_dim); 
    for (unsigned int i = 0; i < tmp.m_dim; i++) {
        tmp.m_pointer[i] = m_pointer[i] + vector.m_pointer[i]; 
    }
    return tmp;
}

double Vector::operator*(const Vector &vector) const{
    if (vector.m_dim != m_dim)
        throw OutOfRangeException();
    else {
        double res = 0;
        for (int i = 0; i < m_dim; ++i) {
            res += m_pointer[i] * vector.m_pointer[i];
        }
        return res;
    }
}

Vector Vector::operator*(double alpha) const{

    Vector res = *this;
    for(int i = 0; i < m_dim; i++)
        res.m_pointer[i] *= alpha;
    return res;
}

/*
Vector operator*(const Vector &vector, double alpha) {
    return vector * alpha;
}
*/

Vector operator*(double alpha, const Vector &vector){
    //Vector tmp(vector);            //!!! Лишнее копирование. Почему сразу vector использовать нельзя?
                                     //исправила, до этого не работало
    //tmp = tmp * alpha;
    return vector * alpha;
}

std::ostream &operator<<(std::ostream &os, const Vector &other) {
    os << "(";
    for (int i = 0; i < other.m_dim; i++) {
        os << *(other.m_pointer + i);
        if (i + 1 != other.m_dim){
            os << ", ";
        }
    }
    os << ")";
    return os;
}

std::istream &operator>>(std::istream &in, Vector &vec){ //!!! Странно, что vec константный
                                                         //исправила
    //!!! Данный оператор должен спросить новый размер и, если он не равен существующему, выделить память заново (Не исправлено)
    //исправила
    int tmp;
    std::cout << "Input size of vector:" << std::endl;
    in >> tmp;

    if (tmp < 0) throw OutOfRangeException();
    if (vec.m_dim != tmp) {
        delete[] vec.m_pointer;
        vec.m_dim = tmp;
        vec.m_pointer = new double[tmp];
    }
    std::cout << "Input vector values:" << std::endl;
    for (int i = 0; i < vec.m_dim; i++) {
        in >> vec.m_pointer[i]; //!!! Для этого есть []
        //исправила
    }
    return in;
}

double Vector::getLength() const{
    double res = 0;
    for (int i = 0; i < m_dim; i++)
        res += pow(m_pointer[i], 2);
    return sqrt(res);
}

int Vector::getDim() const{
    return m_dim;
}

Vector &Vector::operator+(){
    return *this;
}

Vector Vector::operator-(){
    return -1. * (*this);
};

Vector::operator double() const {
    return getLength();
}

Vector operator+(const Vector &vector1, const Vector &vector2) {
    Vector tmp = vector1;
    return tmp += vector2;
}

Vector operator-(const Vector &vector1, const Vector &vector2) {
    Vector tmp = vector1;
    return tmp -= vector2;
}
