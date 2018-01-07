#pragma once



#include <cassert>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    C > 0
)>
class OpExtractColumn {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R, 1>;
public:

    result_t extract_column(unsigned int cc) const {
        assert(cc < C);
        
        result_t m;
        for(unsigned int r = 0; r < R; ++r)
            m.at(r, 0) = static_cast<cthis_t>(this)->at(r, cc);
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpExtractColumn<M, T, R, C, false> {};

}