#ifndef CLASSES_AND_INHERITANCE_EXCEPTION_H
#define CLASSES_AND_INHERITANCE_EXCEPTION_H
#include <exception>
#include <string>

class OutOfRangeException : public std::exception {
    std::string error;
public:
    OutOfRangeException(const std::string &calledError, const int &index, const int &size) {
        error.assign("Out of range exception:\n" + calledError + "  Index:  " + std::to_string(index) +
                     "  Size of the object:  " + std::to_string(size));
    }

    const char *what() const noexcept override {
        return error.c_str();
    }
};

class WrongSizeException : public std::exception {
    std::string error;
public:
    WrongSizeException(const std::string& calledError, const int& size, const  int& maxSize)
    {
        error.assign("Wrong size exception:\n"+calledError + "  Size:  " + std::to_string(size) + "  Max Size:  " + std::to_string(maxSize));
    }

    const char* what() const noexcept override
    {
        return error.c_str();
    }

};

class DifferentSizesException : public std::exception {
    std::string error = "Different sizes exception:\nObjects do not share sizes";
public:
    const char* what() const noexcept override
    {
        return error.c_str();
    }

};

#endif
