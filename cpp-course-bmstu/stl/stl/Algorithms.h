#pragma once
#include <algorithm>
#include <concepts>
#include <iterator>
#include <cstddef>

template <typename _Iter>
concept conceptIter = requires(_Iter i, _Iter j) {
    {i++} -> std::same_as<_Iter>;
    {++i} -> std::same_as<_Iter&>;
    {i--} -> std::same_as<_Iter>;
    {--i} -> std::same_as<_Iter&>;
    requires std::totally_ordered<_Iter>;
    {*i} -> std::same_as<std::iter_reference_t<_Iter>>;
};

template <typename _Arg, typename _Pred>
concept conceptPred = requires(_Pred p, _Arg arg) {
    {p(*arg)} -> std::convertible_to<bool>;
};

template <typename _Arg, typename _Pred>
concept conceptPredBinary = requires(_Pred p, _Arg arg1, _Arg arg2) {
    {p(*arg1, *arg2)} -> std::convertible_to<bool>;
};

template <typename _Arg, typename _Func>
concept conceptFunc = requires(_Func f, _Arg arg) {
    f(*arg);
};

template <typename _Iter, typename _Pred>
requires conceptIter<_Iter> && conceptPred<_Iter, _Pred>
_Iter findIf(_Iter begin, _Iter end, _Pred pred) {
    for (; begin != end; begin++) {
        if (pred(*begin)) {
            break;
        }
    }
    return begin;
}

template <typename _Iter>
requires conceptIter<_Iter>
_Iter minElement(_Iter begin, _Iter end) {
    _Iter res = begin;
    for (; begin != end; begin++) {
        if (*begin < *res) {
            res = begin;
        }
    }
    return res;
}

template <typename _Iter, typename _Pred>
requires conceptIter<_Iter> && conceptPredBinary<_Iter, _Pred>
_Iter minElement(_Iter begin, _Iter end, _Pred pred) {
    _Iter res = begin;
    for (; begin != end; begin++) {
        if (pred(*begin, *res)) {
            res = begin;
        }
    }
    return res;
}

template <typename _Iter>
requires conceptIter<_Iter>
_Iter maxElement(_Iter begin, _Iter end) {
    _Iter res = begin;
    for (; begin != end; begin++) {
        if (*begin > *res) {
            res = begin;
        }
    }
    return res;
}

template <typename _Iter, typename _Pred>
requires conceptIter<_Iter> && conceptPredBinary<_Iter, _Pred>
_Iter maxElement(_Iter begin, _Iter end, _Pred pred) {
    _Iter res = begin;
    for (; begin != end; begin++) {
        if (pred(*begin, *res)) {
            res = begin;
        }
    }
    return res;
}

template <typename _Iter, typename _Func>
requires conceptIter<_Iter> && conceptFunc<_Iter, _Func>
_Func forEach(_Iter begin, _Iter end, _Func f) {
    for (; begin != end; begin++) {
        f(*begin);
    }
    return f;
}

template <typename _Iter>
requires conceptIter<_Iter>
void Sort(_Iter begin, _Iter end) {
    for (; begin != end; begin++)
        std::iter_swap(begin, minElement(begin, end));
}


template <typename _IterSourceType, typename _IterDestType, typename _Pred>
requires conceptIter<_IterSourceType> && conceptIter<_IterDestType> && conceptPred<_IterSourceType, _Pred>
_IterDestType copyIf(_IterSourceType sourceBegin, _IterSourceType sourceEnd, _IterDestType destBeg, _Pred pred) {
    for (; sourceBegin != sourceEnd; sourceBegin++) {
        if (pred(*sourceBegin)) {
            *destBeg = *sourceBegin;
            ++destBeg;
        }
    }
    return destBeg;
}
