#pragma once

#include <awm/config.hpp>

namespace awm {

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // Is Square ?
    R == C
)>
class Square {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, C, R>;
public:

    constexpr bool is_square() const { return true; } 

    static M<T, R, C> identity() {
        M<T, R, C> m(0);
        for(uint i = 0; i < R; ++i) m.at(i, i) = 1;
        return m;
    }

    bool is_diagonal() const {
        for(uint r = 0; r < R; ++r)
            for(uint c = 0; c < C; ++c)
                if (r != c && static_cast<cthis_t>(this)->at(r, c) != 0)
                    return false;
        return true;
    }

    bool is_upper_triangular() const {
        for(uint r = 1; r < R; ++r)
            for(uint c = 0; c < r; ++c)
                if (r != c && static_cast<cthis_t>(this)->at(r, c) != 0)
                    return false;
        return true;
    }

    bool is_lower_triangular() const {
        for(uint r = 1; r < R; ++r)
            for(uint c = r+1; c < C; ++c)
                if (r != c && static_cast<cthis_t>(this)->at(r, c) != 0)
                    return false;
        return true;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class Square<M, T, R, C, false> {
public:
    constexpr bool is_square() const { return false; } 
};

}