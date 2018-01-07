#pragma once



namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    R == C
)>
class OpIsTriangle {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, C, R>;
public:

    bool is_upper_triangular() const {
        for(unsigned int r = 1; r < R; ++r)
            for(unsigned int c = 0; c < r; ++c)
                if (r != c && static_cast<cthis_t>(this)->at(r, c) != 0)
                    return false;
        return true;
    }

    bool is_lower_triangular() const {
        for(unsigned int r = 1; r < R; ++r)
            for(unsigned int c = r+1; c < C; ++c)
                if (r != c && static_cast<cthis_t>(this)->at(r, c) != 0)
                    return false;
        return true;
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpIsTriangle<M, T, R, C, false> {};

}