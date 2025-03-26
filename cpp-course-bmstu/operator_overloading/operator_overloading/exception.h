#ifndef OPERATOR_OVERLOADING_EXCEPTION_H
#define OPERATOR_OVERLOADING_EXCEPTION_H

#include <exception>
#include <string>

class InCompatibleDimException : public std::exception {
    std::string errorMessage;
public:
    InCompatibleDimException();
    const char* what() const throw() override;
};

class OutOfRangeException : public std::exception {
    std::string errorMessage;
public:
    OutOfRangeException();
    const char* what() const throw() override;
};

#endif //OPERATOR_OVERLOADING_EXCEPTION_H
