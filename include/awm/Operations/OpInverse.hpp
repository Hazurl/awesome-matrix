#pragma once


#include <awm/Operations/OpDeterminant.hpp>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    // Has an inverse ?
    R == C
)>
class OpInverse {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<decltype(std::declval<decltype(std::declval<OpDeterminant<M, T, R-1, C-1>>())>().determinant()), C, R>;
public:

    result_t inversed() const {
        auto d = static_cast<cthis_t>(this)->determinant();
        if (d == 0)
            throw std::overflow_error("Matrix's determinant is 0");
        return static_cast<cthis_t>(this)->adjugate() / d;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T>
class OpInverse<M, T, 0, 0, true> {
    using this_t = M<T, 0, 0>*;
    using cthis_t = const M<T, 0, 0>*;
public:

    M<T, 0, 0> inversed() const {
        return {};
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpInverse<M, T, R, C, false> {};

}