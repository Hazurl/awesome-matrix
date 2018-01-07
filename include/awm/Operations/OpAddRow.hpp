#pragma once



#include <cassert>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    C > 0
)>
class OpAddRow {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R + 1, C>;
public:

    result_t add_column(unsigned int d, M<T, 1, C> const& row) const {
        assert(d <= R);
        
        result_t m;
        for(unsigned int r = 0; r < R; ++r) {
            for(unsigned int c = 0; c < C - 1; ++c)
                m.at(r, c) = (d == r ? static_cast<cthis_t>(this)->at(r >= d ? r - 1 : r, c) : row.at(0, c));
        }
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpAddRow<M, T, R, C, false> {};

}