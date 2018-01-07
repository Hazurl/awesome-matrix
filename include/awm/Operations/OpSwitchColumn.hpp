#pragma once



#include <cassert>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    C > 0
)>
class OpSwitchColumn {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R, C>;
public:

    result_t switch_columns(unsigned int c0, unsigned int c1) const {
        assert(c0 < C && c1 < C);
        
        result_t m;
        for(unsigned int c = 0; c < C; ++c) {
            if (c == c0)
                for(unsigned int r = 0; r < R; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c1);
            else if (c == c1)
                for(unsigned int r = 0; r < R; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c0);
            else
                for(unsigned int r = 0; r < R; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c);
        }
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpSwitchColumn<M, T, R, C, false> {};

}