#pragma once



#include <cassert>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    R > 0
)>
class OpSwitchRow {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R, C>;
public:

    result_t switch_rows(unsigned int r0, unsigned int r1) const {
        assert(r0 < R && r1 < R);
        
        result_t m;
        for(unsigned int r = 0; r < R; ++r) {
            if (r == r0)
                for(unsigned int c = 0; c < C; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r1, c);
            else if (r == r1)
                for(unsigned int c = 0; c < C; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r0, c);
            else
                for(unsigned int c = 0; c < C; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c);
        }
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpSwitchRow<M, T, R, C, false> {};

}