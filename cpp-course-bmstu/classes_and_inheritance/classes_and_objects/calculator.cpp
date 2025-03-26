#include "calculator.h"

unsigned int Calculator::counter_calc = 0;

Calculator::Calculator() : m_first(), m_second(), m_result() {
    ++counter_calc;
}
/*
Calculator::Calculator(const Fraction& p_first, const Fraction& p_second) :
                                        m_first(p_first), m_second(p_second), m_result(){
    ++counter_calc;
}
Calculator::Calculator(const Fraction& p_first, const double p_second) :
                                        m_first(p_first), m_second(p_second), m_result(){
    ++counter_calc;
}
Calculator::Calculator(const double p_first, const Fraction& p_second) :
                                        m_first(p_first), m_second(p_second), m_result(){
    ++counter_calc;
}
Calculator::Calculator(const double p_first, const double p_second):
                                        m_first(p_first), m_second(p_second), m_result(){
    ++counter_calc;
}*/

void Calculator::swap(){
    Fraction tmp = m_first;
    m_first = m_second;
    m_second = tmp;
}

void Calculator::write_res_to_first(){
    m_first = m_result;
}

void Calculator::write_res_to_second(){
    m_second = m_result;
}

void Calculator::power(){
    cout << "(" << m_first << ")" << "^" << "(" << m_second << ")" << " = "
         << (m_result = {pow(m_first.toDouble(), m_second.toDouble())});
}

void Calculator::Calculator::logarithm(){
    cout << "log(" << m_first << ", " << m_second << ")" << " = "
         << (m_result = {log(m_first.toDouble())/log(m_second.toDouble())});
}

void Calculator::add(){
    cout << m_first << " + " << m_second << " = " << (m_result = m_second + m_first);
}

void Calculator::subtract(){
    cout << m_first << " - " << m_second<< " = " << (m_result = m_second - m_first);
}

void Calculator::multiply(){
    cout << m_first << " * " << m_second<< " = " << (m_result = m_second * m_first);
}

void Calculator::divide(){
    cout << m_first << " * " << m_second<< " = " << (m_result = m_second / m_first);
}

std::ostream& operator<<(std::ostream& out, const Calculator& cur){
    out << "First operand: " << cur.m_first << std::endl
        << "Second operand: " << cur.m_second << std::endl
        << "Result of previous operation: " << cur.m_result << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Calculator& cur){
    std::cout << "Input first operand. ";
    in >> cur.m_first;
    std::cout << "Input second operand. ";
    in >> cur.m_second;
    cur.m_result = {};

    return in;
}


void Calculator::getCounterFrac(){
    std::cout << "Fraction objects were created" << m_first.getCounter();
}

 unsigned int Calculator::getCounter(){
     std::cout << "Calculators objects were created: " << counter_calc << std::endl;
     return counter_calc;
 }

/*
double Calculator::power(double n, double p) {
    return pow(n, p);
}

double Calculator::power(double n, const Fraction &p) {
    return pow(n, 1.0 * p.getNum() / p.getDen());
}

Fraction Calculator::power(const Fraction &n, int p) {
    return Fraction(pow(n.getNum(), p), pow(n.getDen(), p));
}

double Calculator::power(const Fraction &n, const Fraction &p) {
    return pow(n.toDouble(), p.toDouble());
}

double Calculator::power(const Fraction &n, double p) {
    return pow(n.toDouble(), p);
}

double Calculator::logarithm(double n, double p) {
    return log(p)/log(n);
}

double Calculator::logarithm(double n, const Fraction &p) {
    return log(p.toDouble())/log(n);
}

double Calculator::logarithm(const Fraction &n, const Fraction &p) {
    return log(p.toDouble())/log(n.toDouble());
}

double Calculator::logarithm(const Fraction &n, double p) {
    return log(p)/log(n.toDouble());
}

double Calculator::add(double a, double b) {
    return a+b;
}

double Calculator::add(const Fraction &a, double b) {
    return a.toDouble()+b;
}

double Calculator::add(double a, const Fraction &b) {
    return a+b.toDouble();
}

Fraction Calculator::add(const Fraction &a, int b) {
    return a+b;
}

Fraction Calculator::add(int a, const Fraction &b) {
    return a+b;
}

Fraction Calculator::add(const Fraction &a, const Fraction &b) {
    return a+b;
}

double Calculator::subtract(double a, double b) {
    return a-b;
}

double Calculator::subtract(const Fraction &a, double b) {
    return a.toDouble()-b;
}

double Calculator::subtract(double a, const Fraction &b) {
    return a-b.toDouble();
}

Fraction Calculator::subtract(const Fraction &a, int b) {
    return a-b;
}

Fraction Calculator::subtract(int a, const Fraction &b) {
    return a-b;
}

Fraction Calculator::subtract(const Fraction &a, const Fraction &b) {
    return a-b;
}

double Calculator::multiply(double a, double b) {
    return a*b;
}

double Calculator::multiply(const Fraction &a, double b) {
    return a.toDouble()*b;
}

double Calculator::multiply(double a, const Fraction &b) {
    return a*b.toDouble();
}

Fraction Calculator::multiply(const Fraction &a, int b) {
    return a*b;
}

Fraction Calculator::multiply(int a, const Fraction &b) {
    return a*b;
}

Fraction Calculator::multiply(const Fraction &a, const Fraction &b) {
    return a*b;
}

double Calculator::divide(double a, double b) {
    return a/b;
}

double Calculator::divide(const Fraction &a, double b) {
    return a.toDouble()/b;
}

double Calculator::divide(double a, const Fraction &b) {
    return a/b.toDouble();
}

Fraction Calculator::divide(const Fraction &a, int b) {
    return a/b;
}

Fraction Calculator::divide(int a, const Fraction &b) {
    return a/b;
}

Fraction Calculator::divide(const Fraction &a, const Fraction &b) {
    return a/b;
}

int Calculator::mod(int a, int b) {
    return a%b;
}

int Calculator::decDiv(int a, int b) {
    return a/b;
}


*/
