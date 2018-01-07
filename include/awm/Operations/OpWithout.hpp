#pragma once



namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    R > 0 && C > 0
)>
class OpWithout {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R-1, C-1>;
public:

    result_t without(unsigned int rr, unsigned int cc) const {
        result_t m;
        for(unsigned int r = 0; r < R - 1; ++r)
            for(unsigned int c = 0; c < C - 1; ++c)
                m.at(r, c) = static_cast<cthis_t>(this)->at((r >= rr ? r + 1 : r), (r >= cc ? c + 1 : r));
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpWithout<M, T, R, C, false> {};

}