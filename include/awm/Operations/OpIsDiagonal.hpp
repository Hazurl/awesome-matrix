#pragma once



namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    R == C
)>
class OpIsDiagonal {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, C, R>;
public:

    bool is_diagonal() const {
        for(unsigned int r = 0; r < R; ++r)
            for(unsigned int c = 0; c < C; ++c)
                if (r != c && static_cast<cthis_t>(this)->at(r, c) != 0)
                    return false;
        return true;
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpIsDiagonal<M, T, R, C, false> {};

}