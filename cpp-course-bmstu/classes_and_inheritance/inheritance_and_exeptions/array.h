#ifndef CLASSES_AND_INHERITANCE_ARRAY_H
#define CLASSES_AND_INHERITANCE_ARRAY_H
#include <iostream>

class Array {
protected:
    static const size_t maxSize = 100;
    unsigned char arr[maxSize];
    int size;
public:
    Array();
    explicit Array(int newSize, unsigned char value);
    Array(int newSize, const unsigned char *newArr);
    
    
    //Array(const Array &a);
    //!!! Где тогда operator=? Или конструктор копирования уберите.
    //убрала
    
    virtual ~Array() = default;
    //!!! Виртуальный деструктор?
    //исправила
    
    
    unsigned char &operator[](int ind);
    virtual void arrSum(const Array &other, Array &result) const;
    int getSize() const;
    void setSize(int newSize);
    static size_t getMaxSize();
    const unsigned char& operator[](int ind) const;
    
    virtual const std::string toString() const;
    friend std::ostream &operator<<(std::ostream& out, const Array& arr);
};

//const int Array::maxSize;

#endif
