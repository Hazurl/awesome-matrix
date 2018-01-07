#pragma once


#include <awm/Operations/OpDeterminant.hpp>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    // Has an adjugate ?
    R == C
)>
class OpAdjugate {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<decltype(std::declval<decltype(std::declval<OpDeterminant<M, T, R-1, C-1>>())>().determinant()), C, R>;
public:

    result_t adjugate() const {
        return static_cast<cthis_t>(this)->cofactors().transposed();
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T>
class OpAdjugate<M, T, 0, 0, true> {
    using this_t = M<T, 0, 0>*;
    using cthis_t = const M<T, 0, 0>*;
public:

    M<T, 0, 0> adjugate() const {
        return {};
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpAdjugate<M, T, R, C, false> {};

}