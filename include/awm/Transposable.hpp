#pragma once

#include <awm/config.hpp>

namespace awm {

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // Is transposable ?
    true
)>
class Transposable {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, C, R>;
public:

    result_t transposed() const {
        result_t m;
        for(uint r = 0; r < R; ++r)
            for(uint c = 0; c < C; ++c)
                m.at(c, r) = static_cast<cthis_t>(this)->at(r, c);
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class Transposable<M, T, R, C, false> {};

}