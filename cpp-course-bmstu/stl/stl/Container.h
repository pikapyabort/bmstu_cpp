#pragma once
#include <initializer_list>
#include <iostream>
#include "Iterator.h"
#include "Exceptions.h"



template <typename _DataType>
class Vector {
public:
    using Iterator = VectorIterator<_DataType>;

    Vector() : data_start(nullptr), size_end(nullptr), capacity_end(nullptr) {}

    explicit Vector(int size) {
        data_start = new _DataType[size * 2];
        size_end = data_start + size;

        capacity_end = data_start + size * 2;
    }

    Vector(int size, const _DataType& init_value) {
        data_start = new _DataType[size * 2];
        size_end = data_start + size;
        capacity_end = data_start + size * 2;
        for (int i = 0; i < size; i++)
            data_start[i] = init_value;
    }

    template<typename _Iter>
    Vector(_Iter begin, _Iter end) {
        size_t size = 0;
        for (auto i = begin; i != end; i++)
            size++;
        data_start = new _DataType[size * 2];
        size_end = data_start + size;
        capacity_end = data_start + size * 2;
        _DataType* ptr = data_start;
        for (; begin != end; ++begin) {
            *(ptr++) = *begin;
        }
    }

    Vector(const std::initializer_list<_DataType> &list) {
        data_start = new _DataType[list.size() * 2];
        size_end = data_start + list.size();
        capacity_end = data_start + list.size() * 2;

        _DataType* pos = data_start;
        for (auto it = list.begin(); it != list.end(); it++)
            *(pos++) = *it;
    }

    Vector(const Vector& v) {
        std::size_t capacity = v.capacity();
        std::size_t size = v.size();
        data_start = new _DataType[capacity];
        size_end = data_start + size;
        capacity_end = data_start + capacity;
        for (int i = 0; i < size; i++)
            data_start[i] = v.data_start[i];
    }

    Vector(Vector<_DataType>&& v) noexcept {
        data_start = v.data_start;
        size_end = v.size_end;
        capacity_end = v.capacity_end;

        v.data_start = nullptr;
        v.size_end = nullptr;
        v.capacity_end = nullptr;
    }

    ~Vector() {
        delete[] data_start;
    }

    Vector& operator=(const Vector& v) {
        if (this == &v)
            return *this;
        delete[] data_start;
        data_start = new _DataType[v.capacity()];
        for (int i = 0; i < v.size(); i++)
            data_start[i] = v[i];
        size_end = data_start + v.size();
        capacity_end = data_start + v.capacity();
        return *this;
    }

    Vector& operator=(Vector&& v) noexcept {
        if (this == &v)
            return *this;
        delete[] data_start;
        std::size_t size = v.size();
        std::size_t capacity = v.capacity();
        data_start = v.data_start;
        size_end = data_start + size;
        capacity_end = data_start + capacity;

        v.data_start = nullptr;
        v.size_end = nullptr;
        v.capacity_end = nullptr;
        return *this;
    }

    _DataType& operator[](const int index) {
        return data_start[index];
    }

    const _DataType& operator[](const int index) const {
        return data_start[index];
    }


    _DataType& at(const int index) {
        if ((index < 0) || (index >= size()))
            throw OutOfRangeException();
        return data_start[index];
    }

    const _DataType& at(const int index) const {
        if ((index < 0) || (index >= size()))
            throw OutOfRangeException();
        return data_start[index];
    }

    Iterator begin() {
        return Iterator(data_start);
    }

    Iterator end() {
        return Iterator(size_end);
    }

    void pushBack(const _DataType& elem) {
        if (size_end == capacity_end)
            reserve(capacity());
        *(size_end++) = elem;
    }

    void pushBack(_DataType&& elem) noexcept {
        if (size_end == capacity_end)
            reserve(capacity());
        *(size_end++) = std::move(elem);
    }


    _DataType& popBack() {
        if (empty())
            throw EmptyVectorException();
        _DataType& tmp =  *(--size_end);
        
        
        return tmp; //!!! Это лишнее
    }

    Iterator insert(Iterator pos, const _DataType& elem) {
        Iterator temp = begin();
        if (size_end == capacity_end) {
            if (capacity() == 0)
                reserve(1);
            else
                reserve(capacity());
        }
        for (int i = size(); i > pos - temp; i--) {
            data_start[i] = data_start[i - 1];
        }
        data_start[pos - temp] = elem;
        size_end++;
        return pos;
    }

    template<typename _Iter>
    Iterator insert(Iterator pos, _Iter _begin, _Iter _end) {
        std::size_t _size = _end - _begin;
        int _posInd = pos - begin();
        auto* temp = new _DataType[_size];
        int _j = 0;
        for (_Iter i = _begin; i != _end; i++, _j++) {
            temp[_j] = *i;
        }
        resize(size() + _size);
        for (int i = size() - 1; i >= _posInd + _size; i--) {
            data_start[i] = data_start[i - _size];
        }
        Iterator j(temp);
        for (int i = _posInd; i < _posInd + _size; i++, j++) {
            data_start[i] = *j;
        }
        delete[] temp;
        return pos;
    }

    Iterator erase(Iterator pos) {
        for (auto i = pos; i != end() - 1; i++) {
            *i = *(i + 1);
        }
        popBack();
        return pos;
    }



    template<class... Args>
    void emplace_back(Args&&... args) {

        pushBack(_DataType(std::forward<Args>(args)...));
    }


    void reserve(const std::size_t n) {
        if (n < 0)
            throw WrongSizeException();
        if (!capacity_end) {
            data_start = new _DataType[2];
            size_end = data_start;
            capacity_end = data_start + 2;
            return;
        }
        if (size() + n <= capacity())
            capacity_end = size_end + n;
        else {
            std::size_t new_capacity = size() + n;
            auto new_data = new _DataType[new_capacity];
            std::size_t old_size = size();
            for (int i = 0; i < old_size; i++)
                new_data[i] = data_start[i];
            delete[] data_start;
            data_start = new_data;
            size_end = data_start + old_size;
            capacity_end = data_start + new_capacity;
        }
    }

    void resize(const std::size_t n) {
        if (n < 0)
            throw WrongSizeException();
        if (n > size())
            for (int i = size(); i < n; i++)
                pushBack(_DataType());
        else
            for (int i = size() - 1; i >= n; i--)
                popBack();
        size_end = data_start + n;
    };

    [[nodiscard]] bool empty() const {
        return size() == 0;
    }

    [[nodiscard]] std::size_t size() const {
        return size_end - data_start;
    }

    [[nodiscard]] std::size_t capacity() const {
        return capacity_end - data_start;
    }

    void clear() {
        size_end = data_start;
    }

private:
    _DataType* data_start;
    _DataType* size_end;
    _DataType* capacity_end;
};
