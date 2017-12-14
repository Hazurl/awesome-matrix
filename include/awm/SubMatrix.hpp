#pragma once

#include <awm/config.hpp>

namespace awm {

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    true
)>
class SubMatrix {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
public:

    template<uint RR, uint CC>
    M<T, RR, CC> submatrix(uint r0, uint c0) const {
        M<T, RR, CC> m;
        for(uint r = r0; r < r0+RR; ++r)
            for(uint c = c0; c < c0+CC; ++c)
                m.at(r-r0, c-c0) = static_cast<cthis_t>(this)->at(r, c);
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class SubMatrix<M, T, R, C, false> {};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    R > 1 && C > 1
)>
class Without {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R-1, C-1>;
public:

    result_t without(uint rr, uint cc) const {
        result_t m;
        for(uint r = 0; r < R - 1; ++r)
            for(uint c = 0; c < C - 1; ++c)
                m.at(r, c) = static_cast<cthis_t>(this)->at((r >= rr ? r + 1 : r), (r >= cc ? c + 1 : r));
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class Without<M, T, R, C, false> {};

}