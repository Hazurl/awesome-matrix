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

    template<uint R0, uint C0, uint RR, uint CC>
    M<T, RR, CC> submatrix() const {
        M<T, RR, CC> m;
        for(uint r = R0; r < R0+RR; ++r)
            for(uint c = C0; c < C0+CC; ++c)
                m.at(r-R0, c-C0) = static_cast<cthis_t>(this)->at(r, c);
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class SubMatrix<M, T, R, C, false> {};

}