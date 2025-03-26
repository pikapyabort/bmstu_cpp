#include "bitstring.h"


BitString BitString::andFunc(const BitString &a) {
    if (size != a.size)
        throw DifferentSizesException();
    BitString s(size, '0');
    for (int i = 0; i < size; ++i) {
        if (arr[i] == '1' && a.arr[i] == '1')
            s.arr[i] = '1';
    }
    return s;
}

BitString::BitString(int newSize, const unsigned char *newArr): Array(newSize, newArr) {}

BitString BitString::orFunc(const BitString &a) {
    if (size != a.size)
        throw DifferentSizesException();
    BitString s(size, '1');
    for (int i = 0; i < size; ++i) {
        if (arr[i] == '0' && a.arr[i] == '0')
            s.arr[i] = '0';
    }
    return s;
}

BitString BitString::xorFunc(const BitString &a) {
    if (size != a.size)
        throw DifferentSizesException();
    BitString s(size, '1');
    for (int i = 0; i < size; ++i) {
        if (arr[i] == a.arr[i])
            s.arr[i] = '0';
    }
    return s;
}

BitString BitString::notFunc() {
    BitString s(size, '0');
    for (int i = 0; i < size; ++i) {
        if (arr[i] == '0')
            s.arr[i] = '1';
    }
    return s;
}

BitString::BitString(int newSize, unsigned char value) : Array(newSize, value) {}

void BitString::arrSum(const Array& p_other, Array& p_result) const {
    unsigned int size = getSize();
    unsigned int other_size = p_other.getSize();

    if (getSize() != p_other.getSize()) {
        throw DifferentSizesException();
    }

    p_result.setSize(size);

    for (int i = 0; i < size; i++) {
        if ((arr[i] == '1') || (p_other[i] == '1')) {
            if ((arr[i] == '1') && (p_other[i] == '1')) {
                p_result[i] = '0';
            }
            else {
                p_result[i] = '1';
            }
        }
        else {
            p_result[i] = '0';
        }
    }
}

/*void BitString::arrSum(const Array *a, Array *b) {

    //!!! Где проверка правильности приведения?
    //!!! И вообще нужна ли она? Она делается только чтобы вызвать то, что не видно через указатель на базовый класс.
    //исправила
    b->size = size;
    if (b->size != a->size)
        throw DifferentSizesException();
    for (int i = 0; i < b->size; ++i) {
        if (arr[i] == a->arr[i])
            b->arr[i] = '0';
        else
            b->arr[i] = '1';
    }
}*/

const std::string BitString::toString() const {
    std::string s;
    for (int i = 0; i < size; i++)
        s += arr[i];
    return s;
}


std::istream& operator>>(std::istream& in, BitString& cur){
    char str[151];
	std::cout << "Input binary string: ";
	in >> str;
    cur.setSize(strlen(str));

    for (int i = 0; i < strlen(str); ++i) {
		if (str[i] - 48 > 0) {
			cur[i] = '1';
		}
		else {
			cur[i] = '0';
		}
	}

	return in;
}
