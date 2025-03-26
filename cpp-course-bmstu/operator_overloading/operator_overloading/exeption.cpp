#include "exception.h"

InCompatibleDimException::InCompatibleDimException()
        :errorMessage("Error: Vector and CSRMatrix are not of the same size")
{}

const char* InCompatibleDimException::what() const throw(){
    return errorMessage.c_str();
}

OutOfRangeException::OutOfRangeException()
        :errorMessage("Error: Operation between vectors can't be done! They are not of the same size.")
{}

const char* OutOfRangeException::what() const throw(){
    return errorMessage.c_str();
}