#pragma once



#include <cassert>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    R > 0
)>
class OpExtractRow {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, 1, C>;
public:

    result_t extract_row(unsigned int rr) const {
        assert(rr < R);
        
        result_t m;
        for(unsigned int c = 0; c < C; ++c)
            m.at(0, c) = static_cast<cthis_t>(this)->at(rr, c);
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpExtractRow<M, T, R, C, false> {};

}