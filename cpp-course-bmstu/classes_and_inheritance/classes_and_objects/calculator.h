#pragma once
#include "fraction.h"
#include <cmath>

class Calculator {
    
    //!!! В первой части ДЗ предполагается, что данный класс должен 
    //!!! использовать делегирование (создать объекты второго класса, как поля)
    //исправила...
    Fraction m_first;
    Fraction m_second;
    Fraction m_result;
    static unsigned int counter_calc;
public:

    Calculator();
    /*Calculator(const Fraction&, const Fraction&);
    Calculator(const Fraction&, const double);
    Calculator(const double, const Fraction&);
    Calculator(const double, const double);
*/
    void swap();
    void write_res_to_first();
    void write_res_to_second();

    void power();
    void logarithm();

    void add();
    void subtract();
    void multiply();
    void divide();

    friend std::ostream& operator<<(std::ostream& out, const Calculator& cur);
    friend std::istream& operator>>(std::istream& in, Calculator& cur);

    static unsigned int getCounter();
    void getCounterFrac();

    /*   static double power(double n, double p);
       static double power(double n, const Fraction& p);
       static Fraction power(const Fraction& n, int p);
       static double power(const Fraction& n, const Fraction& p);
       static double power(const Fraction& n, double p);

       static double logarithm(double n, double p);
       static double logarithm(double n, const Fraction& p);
       static double logarithm(const Fraction& n, const Fraction& p);
       static double logarithm(const Fraction& n, double p);

       static double add(double a, double b);
       static double add(const Fraction& a, double b);
       static double add(double a, const Fraction& b);
       static Fraction add(const Fraction& a, int b);
       static Fraction add(int a, const Fraction& b);
       static Fraction add(const Fraction& a, const Fraction& b);

       static double subtract(double a, double b);
       static double subtract(const Fraction& a, double b);
       static double subtract(double a, const Fraction& b);
       static Fraction subtract(const Fraction& a, int b);
       static Fraction subtract(int a, const Fraction& b);
       static Fraction subtract(const Fraction& a, const Fraction& b);

       static double multiply(double a, double b);
       static double multiply(const Fraction& a, double b);
       static double multiply(double a, const Fraction& b);
       static Fraction multiply(const Fraction& a, int b);
       static Fraction multiply(int a, const Fraction& b);
       static Fraction multiply(const Fraction& a, const Fraction& b);

       static double divide(double a, double b);
       static double divide(const Fraction& a, double b);
       static double divide(double a, const Fraction& b);
       static Fraction divide(const Fraction& a, int b);
       static Fraction divide(int a, const Fraction& b);
       static Fraction divide(const Fraction& a, const Fraction& b);

       static int mod(int a, int b);
       static int decDiv(int a, int b);*/
};

//unsigned int Calculator::counter_calc = 0;