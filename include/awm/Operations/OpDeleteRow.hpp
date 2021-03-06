#pragma once



#include <cassert>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    R > 0
)>
class OpDeleteRow {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R - 1, C>;
public:

    result_t delete_row(unsigned int d) const {
        assert(d < R);
        
        result_t m;
        for(unsigned int r = 0; r < R - 1; ++r) {
            for(unsigned int c = 0; c < C; ++c)
                m.at(r, c) = static_cast<cthis_t>(this)->at((r >= d ? r + 1 : r), c);
        }
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpDeleteRow<M, T, R, C, false> {};

}