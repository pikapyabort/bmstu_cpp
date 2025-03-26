#pragma once
#include <exception>
#include <cstdio>
#include "Exceptions.h"

template <typename _DataType>
class VectorIterator {
public:
    VectorIterator() : ptr(nullptr) {}
    explicit VectorIterator(_DataType* ptr) : ptr(ptr) {}
    VectorIterator(const VectorIterator<_DataType>& it) : ptr(it.ptr) {}

    VectorIterator<_DataType> operator++(int) {
        if (ptr) {
            VectorIterator<_DataType> cur = *this;
            ptr++;
            return cur;
        }
        throw EmptyIteratorException();
    }

    VectorIterator<_DataType>& operator++() {
        if (ptr) {
            ptr++;
            return *this;
        }
        throw EmptyIteratorException();
    }

    VectorIterator<_DataType> operator--(int) {
        if (ptr) {
            VectorIterator<_DataType> cur = *this;
            ptr--;
            return cur;
        }
        throw EmptyIteratorException();
    }

    VectorIterator<_DataType>& operator--() {
        if (ptr) {
            ptr--;
            return *this;
        }
        throw EmptyIteratorException();
    }

    _DataType& operator*() const {
        if (ptr)
            return *ptr;
        throw EmptyIteratorException();
    }

    VectorIterator<_DataType>& operator=(const VectorIterator<_DataType>& it) {
        if (this == &it)
            return *this;
        ptr = it.ptr;
        return *this;
    }

    int operator-(const VectorIterator& it) {
        return ptr - it.ptr;
    }

    auto operator<=>(const VectorIterator& it) const = default;

    VectorIterator<_DataType>& operator+=(const int n) {
        if (ptr) {
            ptr += n;
            return *this;
        }
        throw EmptyIteratorException();
    }

    VectorIterator<_DataType>& operator-=(const int n) {
        if (ptr) {
            ptr -= n;
            return *this;
        }
        throw EmptyIteratorException();
    }

    _DataType* operator->() const noexcept {

        return ptr;
    }

    explicit operator _DataType*() {
        return ptr;
    }

    _DataType& operator[](size_t i) {
        if (i < 0)
            throw OutOfRangeException();

        return *(ptr + i);
    }

    const _DataType& operator[](size_t i) const {
        if (i < 0)
            throw OutOfRangeException();

        return *(ptr + i);
    }

private:
    _DataType* ptr;
};

template <typename _DataType>
VectorIterator<_DataType> operator+(VectorIterator<_DataType> it, const int n) {
    return it += n;
}

template <typename _DataType>
VectorIterator<_DataType> operator-(VectorIterator<_DataType> it, const int n) {
    return it -= n;
}
