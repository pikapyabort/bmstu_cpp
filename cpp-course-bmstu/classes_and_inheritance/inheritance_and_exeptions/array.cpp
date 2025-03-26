#include "array.h"
#include "exception.h"

unsigned char &Array::operator[](int i) {
    if (i > size || i < 0)
        throw OutOfRangeException("Index is out of range;", i, size);
    return arr[i];
}

const unsigned char& Array::operator [](int ind) const {
    if ((ind >= size) || (ind < 0)) {
        throw OutOfRangeException("Index is out of range;", ind, size);
    }
    return arr[ind];
}

Array::Array(int newSize, const unsigned char *newArr) {
    if (newSize > maxSize || newSize < 0)
        throw WrongSizeException("The size is negative of bigger than max size;", newSize, maxSize);
    size = newSize;
    for (int i = 0; i < newSize; ++i) {
        arr[i] = newArr[i];
    }
}

Array::Array(const Array &a) : size(a.size) {
    for (int i = 0; i < size; i++)
        arr[i] = a.arr[i];
}

Array::Array(int newSize, unsigned char value) {
    if (newSize > maxSize || newSize < 0)
        throw WrongSizeException("The size is negative of bigger than max size;", newSize, maxSize);
    size = newSize;
    for (int i = 0; i < newSize; ++i)
        arr[i] = value;
}

void Array::arrSum(const Array &other, Array &result) const{ //!!! Дайте осознанные имена параметрам. b как будто второй операнд...
//исправила
    if (other.size != size)
        throw DifferentSizesException();
    result.size = size;
    
    for (int i = 0; i < size; i++) {
        result.arr[i] = other.arr[i] + arr[i];
    }
}

int Array::getSize() const {
    return size;
}

void Array::setSize(int newSize) {
    size = newSize;
}

const std::string Array::toString() const {
    std::string s;
    for (int i = 0; i < size; i++)
        s += arr[i];
    return s;
}

std::ostream &operator<<(std::ostream &out, const Array &arr) {
        out << arr.toString();
    return out;
}

Array::Array() : size(0) {}

size_t Array::getMaxSize(){
    return maxSize;
}

//Array::~Array() = default; //!!! Это делается при объявлении. Только вопрос вообще зачем деструктор явно объявлять
//исправила

