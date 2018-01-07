#pragma once

#include <initializer_list>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    R == C
)>
class CtorDiagonal {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R, C>;
public:

    static result_t diagonal(std::initializer_list<T> const& il) {
        result_t m(0);
        auto b = il.begin();
        for(unsigned int i = 0; i < R; ++i) m.at(i, i) = *b, ++b;
        return m;
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class CtorDiagonal<M, T, R, C, false> {};

}