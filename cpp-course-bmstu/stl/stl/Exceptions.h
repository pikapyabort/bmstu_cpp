#pragma once
#include <exception>


class EmptyIteratorException : public std::exception {
public:
    const char *what() const noexcept override {
        return "Error: the iterator is empty!";
    }
};

class EmptyVectorException : public std::exception {
public:
    const char *what() const noexcept override {
            return "Error: trying to get access to empty vector!";
    }
};

class WrongSizeException : public std::exception {
public:
    const char *what() const noexcept override {
            return "Error: wrong size!";
    }
};

class OutOfRangeException : public std::exception {
public:
    const char *what() const noexcept override {
            return "Error: wrong size!";
    }
};
