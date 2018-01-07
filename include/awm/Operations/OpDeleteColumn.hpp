#pragma once



#include <cassert>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    C > 0
)>
class OpDeleteColumn {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R, C - 1>;
public:

    result_t delete_column(unsigned int d) const {
        assert(d < C);
        
        result_t m;
        for(unsigned int r = 0; r < R; ++r) {
            for(unsigned int c = 0; c < C - 1; ++c)
                m.at(r, c) = static_cast<cthis_t>(this)->at(r, (c >= d ? c + 1 : c));
        }
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpDeleteColumn<M, T, R, C, false> {};

}