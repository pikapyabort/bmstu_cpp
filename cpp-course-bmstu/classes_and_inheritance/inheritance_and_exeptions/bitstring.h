#ifndef CLASSES_AND_INHERITANCE_BITSTRING_H
#define CLASSES_AND_INHERITANCE_BITSTRING_H
#include "array.h"
#include "bitstring.h"
#include "exception.h"

class BitString : public Array {
public:
    BitString(int newSize, const unsigned char *newArr);
    explicit BitString(int newSize = 0, unsigned char value = '0');
    BitString andFunc(const BitString &a);
    BitString orFunc(const BitString &a);
    BitString xorFunc(const BitString &a);
    BitString notFunc();
    void arrSum(const Array& p_other, Array& p_result) const override;//!!! Где override?
    //добавила
    const std::string toString() const override;
    friend std::istream& operator>>(std::istream& in, BitString& cur);
};

#endif
