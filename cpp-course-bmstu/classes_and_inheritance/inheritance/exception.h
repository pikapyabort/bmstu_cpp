#ifndef INHERITANCE_EXCEPTION_H
#define INHERITANCE_EXCEPTION_H
#include <exception>
#include <string>

using std::string;

class WrongValueException : public std::exception {
    string error;
public:
    WrongValueException(const string &calledError, const double &sum) {
        error.assign("Wrong sum exception:\n" + calledError + "  sum:  " + std::to_string(sum));
    }
    const char *what() const noexcept override {
        return error.c_str();
    }
};

#endif //INHERITANCE_EXCEPTION_H
