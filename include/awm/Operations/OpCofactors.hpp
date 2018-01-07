#pragma once


#include <awm/Operations/OpDeterminant.hpp>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    R == C
)>
class OpCofactors {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<decltype(std::declval<decltype(std::declval<OpDeterminant<M, T, R-1, C-1>>())>().determinant()), R, C>;
public:

    result_t cofactors() const {
        result_t m = static_cast<cthis_t>(this)->minors();
        for(unsigned int r = 0; r < R; ++r)
            for(unsigned int c = 0; c < C; ++c)
                m.at(r, c) *= ((r+c) % 2 == 0) ? 1 : -1;
        return m;
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T>
class OpCofactors<M, T, 0, 0, true> {
    using this_t = M<T, 0, 0>*;
    using cthis_t = const M<T, 0, 0>*;
public:

    auto cofactors() const {
        return static_cast<cthis_t>(this)->minors();
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T>
class OpCofactors<M, T, 1, 1, true> {
    using this_t = M<T, 1, 1>*;
    using cthis_t = const M<T, 1, 1>*;
    using result_t = M<decltype(std::declval<decltype(std::declval<OpDeterminant<M, T, 0, 0>>())>().determinant()), 1, 1>;
public:

    result_t cofactors() const {
        return static_cast<cthis_t>(this)->minors();
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T>
class OpCofactors<M, T, 2, 2, true> {
    using this_t = M<T, 2, 2>*;
    using cthis_t = const M<T, 2, 2>*;
    using result_t = M<T, 2, 2>;
public:

    result_t cofactors() const {
        return { static_cast<cthis_t>(this)->at(1, 1),
                -static_cast<cthis_t>(this)->at(1, 0),
                -static_cast<cthis_t>(this)->at(0, 1),
                 static_cast<cthis_t>(this)->at(0, 0) };
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpCofactors<M, T, R, C, false> {};

}