#include "application.h"


 Application::Application() : m_flagMenu(true), m_option(0) {}

void Application::run(){
    m_flagMenu = true;

    while (m_flagMenu) {
        std::cout << std::endl << "Menu:" << std::endl
                  << "1. initialize calculator" << std::endl
                  << "2. print operands" << std::endl
                  << "3. swap operands"<< std::endl
                  << "4. perform mathematical operation" << std::endl
                  << "5. write result to first operand" << std::endl
                  << "6. write result to second operand" << std::endl
                  << "7. output fraction and calculator counters" << std::endl
                  << "! print 0 to exit" << std::endl;
        std::cin >> m_option;

        switch (m_option) {
            case 0:
                m_flagMenu = false;
                break;
            case 1:
                std::cin >> m_calculator;
                break;
            case 2:
                std::cout << m_calculator;
                break;
             case 3:
                 m_calculator.swap();
                 break;
             case 4:
                 math();
                 break;
             case 5:
                 m_calculator.write_res_to_first();
                 break;
             case 6:
                 m_calculator.write_res_to_second();
                 break;
             case 7:
                 Calculator::getCounter();
                 Fraction::getCounter();
                 //m_calculator.getCounterFrac();
                 break;
            default:
                std::cout<< "No such option!" << std::endl;
                break;
        }

    }
}

void Application::math() {
    bool flagMath= true;
    while (flagMath) {
        std::cout << std::endl << "Operations:" << std::endl
                  << "1. sum" << std::endl
                  << "2. subtract" << std::endl
                  << "3. multiply"<< std::endl << std::endl
                  << "4. divide" << std::endl
                  << "5. power" << std::endl
                  << "6. logarithm" << std::endl << std::endl
                  << "7. write result to first operand" << std::endl
                  << "8. write result to second operand" << std::endl
                  << "! print 0 to exit to main menu" << std::endl;
        std::cin >> m_option;

        switch (m_option) {
            case 0:
                flagMath = false;
                break;
            case 1:
                m_calculator.add();
                break;
            case 2:
                m_calculator.subtract();
                break;
            case 3:
                m_calculator.multiply();
                break;
            case 4:
                m_calculator.divide();
                break;
            case 5:
                m_calculator.power();
                break;
            case 6:
                m_calculator.logarithm();
                break;
            case 7:
                m_calculator.write_res_to_first();
                break;
            case 8:
                m_calculator.write_res_to_second();
                break;
            default:
                std::cout << "Wrong key!" << std::endl;
                break;
        }
    }
}



//void Application::run(){



    /*Fraction frac_1, frac_2;
    int int_1, int_2;
    double double_1, double_2;
    cout << "Input 2 fractions (in format numerator/denominator):" << endl;
    cin >> frac_1 >> frac_2;
    cout << "Fraction frac_1: " << frac_1 << endl << "Fraction frac_2: " << frac_2 << endl;
    cout << "frac_1 + frac_2 = " << frac_1 + frac_2 << endl
         << "frac_1 - frac_2 = " << frac_1 - frac_2 << endl
         << "frac_1 * frac_2 = " << frac_1 * frac_2 << endl
         << "frac_1 / frac_2 = " << frac_1 / frac_2 << endl
         << "frac_1 == frac_2: " << std::boolalpha << (frac_1 == frac_2) << endl
         << "frac_1 < frac_2: " << std::boolalpha << (frac_1 < frac_2) << endl
         << "frac_1 > frac_2: " << std::boolalpha << (frac_1 > frac_2) << endl;
    cout << "Input 2 integers (int_1, int_2):" << std::endl;
    cin >> int_1 >> int_2;
    cout << "int_1 + int_2 = " << int_1 + int_2 << std::endl
         << "int_1 - int_2  = " << int_1 - int_2 << std::endl
         << "int_1 * int_2 = " << int_1 * int_2 << std::endl
         << "int_1 / int_2 = " << int_1 / int_2 << std::endl;

    cout << "Input 2 double numbers (double_1, double_2):" << std::endl;
    cin >> double_1 >> double_2;
    cout << endl << "Addition of 2 numbers:" << endl
         << "double_1 + double_2 = " << Calculator::add(double_1, double_2) << endl
         << "frac_1 + double_1 = " << Calculator::add(frac_1, double_1) << endl
         << "double_1 + frac_1 = " << Calculator::add(double_1, frac_1) << endl
         << "frac_1 + int_2 = " << Calculator::add(frac_1, int_2) << endl
         << "int_2 + frac_1 = " << Calculator::add(int_2, frac_1) << endl
         << "frac_1 + frac_2 = " << Calculator::add(frac_1, frac_2) << endl
         << std::endl << "Subtraction of 2 numbers:" << endl
         << "double_1 - double_2 = " << Calculator::subtract(double_1, double_2) << endl
         << "frac_1 - double_1 = " << Calculator::subtract(frac_1, double_1) << endl
         << "double_1 - frac_1 = " << Calculator::subtract(double_1, frac_1) << endl
         << "frac_1 - int_2 = " << Calculator::subtract(frac_1, int_2) << endl
         << "frac_1 - frac_2 = " << Calculator::subtract(frac_1, frac_2) << endl
         << "int_2 - frac_1 = " << Calculator::subtract(int_2, frac_1) << endl
         << std::endl << "Multiplication of 2 numbers:" << std::endl
         << "double_1 * double_2 = " << Calculator::multiply(double_1, double_2) << endl
         << "frac_1 * double_1 = " << Calculator::multiply(frac_1, double_1) << endl
         << "double_1 * frac_1 = " << Calculator::multiply(double_1, frac_1) << endl
         << "frac_1 * d = " << Calculator::multiply(frac_1, int_2) << endl
         << "int_2 * frac_1 = " << Calculator::multiply(int_2, frac_1) << endl
         << "frac_1 * frac_2 = " << Calculator::multiply(frac_1, frac_2) << endl
         << std::endl << "Division of 2 numbers:" << endl
         << "double_1 / double_2 = " << Calculator::divide(double_1, double_2) << endl
         << "frac_1 / double_1 = " << Calculator::divide(frac_1, double_1) << endl
         << "double_1 / frac_1 = " << Calculator::divide(double_1, frac_1) << endl
         << "frac_1 / int_2 = " << Calculator::divide(frac_1, int_2) << endl
         << "int_2 / frac_1 = " << Calculator::divide(int_2, frac_1) << endl
         << "frac_1 / frac_2 = " << Calculator::divide(frac_1, frac_2) << endl
         << std::endl << "Power function:" << endl
         << "double_1 ^ double_2 = " << Calculator::power(double_1, double_2) << endl
         << "double_1 ^ frac_1 = " << Calculator::power(double_1, frac_1) << endl
         << "frac_1 ^ int_2 = " << Calculator::power(frac_1, int_2) << endl
         << "frac_1 ^ frac_2 = " << Calculator::power(frac_1, frac_2) << endl
         << "frac_1 ^ double_1 = " << Calculator::power(frac_1, double_1) << endl
         << std::endl << "Logarithm function:" << endl
         << "log(double_1, double_2) = " << Calculator::logarithm(double_1, double_1) << endl
         << "log(f, frac_1) = " << Calculator::logarithm(double_1, frac_1) << endl
         << "log(frac_1, frac_2) = " << Calculator::logarithm(frac_1, frac_2) << endl
         << "log(frac_1, double_1) = " << Calculator::logarithm(frac_1, double_1) << endl
         << std::endl << "Decimal division function:" << endl
         << "int_1 div int_2 = " << Calculator::decDiv(int_1, int_2) << endl
         << std::endl << "Remainder from division function:" << endl
         << "int_1 mod int_2 = " << Calculator::mod(int_1, int_2) << endl;*/
//}