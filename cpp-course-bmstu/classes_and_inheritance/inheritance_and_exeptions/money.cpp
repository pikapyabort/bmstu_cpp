#include <iostream>
#include <cmath>
#include "money.h"


void Money::arrSum(const Array &p_other, Array &p_result) const{

    p_result.setSize(size);
    if (p_result.getSize() < p_other.getSize())
        p_result.setSize(p_other.getSize());

    int res_size = p_result.getSize();

    for (int i = 0; i < res_size; ++i)
        p_result[i] = 0;

    for (int i = 0; i < res_size - 1; ++i) {
        p_result[i] += arr[i] + p_other[i] - (int) '0';
        if ((int) p_result[i] - (int) '0' > 9) {
            p_result[i] -= 10;
            ++p_result[i + 1];
        }
    }

    p_result[res_size - 1] = arr[res_size - 1] + p_other[res_size - 1] - (int) '0';

    if ((int) p_result[res_size - 1] - (int) '0' > 9) {
        p_result[res_size - 1] -= 10;
        ++p_result[res_size];
        p_result.setSize(++res_size);
    }

    // const auto& p_other = dynamic_cast<const Money&>(p_other);
    // auto& p_result = dynamic_cast<Money&>(p_result);

    // //!!! Где проверка правильности приведения? И нужно ли приведение вообще?
    // //try catch bad_cast в main.cpp

    // p_result.size = size;
    // if (p_result.size < p_other.size)
    //     p_result.size = p_other.size;
    // for (int i = 0; i < p_result.size - 1; ++i) {
    //     p_result.arr[i] = arr[i] + p_other.arr[i] - (int) '0';
    //     if ((int) p_result.arr[i] - (int) '0' > 9) {
    //         p_result.arr[i] -= 10;
    //         ++p_result.arr[i + 1];
    //     }
    // }
    // p_result.arr[p_result.size - 1] = arr[p_result.size - 1] + p_other.arr[p_other.size - 1] - (int) '0';
    // if ((int) p_result.arr[p_result.size - 1] - (int) '0' > 9) {
    //     p_result.arr[p_result.size - 1] -= 10;
    //     ++p_result.arr[p_result.size];
    //     ++p_result.size;
    // }
}


Money::Money(int newSize, const unsigned char *newArr) : Array(newSize, newArr){
    //!!! Инициализацией базовых полей должен заниматься базовый конструктор. Где его вызов?
    //fixed
    // if (newSize > maxSize || newSize < 0)
    //     throw WrongSizeException("The size is negative of bigger than max size;", newSize, maxSize);
    // size = newSize;
    // for (int i = 0; i < newSize; ++i) {
    //     arr[i] = newArr[i];
    // }
    // for (int i = newSize; i < maxSize; ++i) {
    //     arr[i] = '0';
    // }
}

Money::Money(const double d) { ///!!! Какой смысл d по ссылке передавать?
//исправила
    std::string s = std::to_string(std::round(d * 100) / 100);
    size = s.size() - 5; 
    arr[0] = s[size];
    arr[1] = s[size-1];
    if (size > maxSize)
        throw WrongSizeException("The size is negative of bigger than max size;", size, maxSize);
    for (int i = 2; i < size; ++i) {
        arr[i] = s[size - i - 1];
    }
    for (int i = size; i < maxSize; ++i) {
        arr[i] = '0';
    }
}

const std::string Money::toString() const {
    std::string s;

    for (int i = size - 1; i > 1; --i)
        s += arr[i];
    ((s += '.') += arr[1]) += arr[0];

    return s;
}

std::ostream &operator<<(std::ostream &out, const Money &m) {
    out << m.toString();
    return out;
}

std::istream &operator>>(std::istream &in, Money &m){
    std::cout << "input amound of money:" << std::endl;
    double d;
    in >> d;
    std::string s = std::to_string(std::round(d * 100) / 100);
     m.size = s.size() - 5;
     m.arr[0] = s[m.size];
     m.arr[1] = s[m.size - 1];
     int maxSize = m.getMaxSize();
     if (m.size > maxSize)
         throw WrongSizeException("The size is negative of bigger than max size;", m.size, maxSize);
     for (int i = 2; i < m.size; ++i) {
         m.arr[i] = s[m.size - i - 1];
     }
     for (int i = m.size; i < maxSize; ++i) {
         m.arr[i] = '0';
     }
    return in;
}