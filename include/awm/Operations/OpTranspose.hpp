#pragma once



namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    true
)>
class OpTranspose {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, C, R>;
public:

    result_t transposed() const {
        result_t m;
        for(unsigned int r = 0; r < R; ++r)
            for(unsigned int c = 0; c < C; ++c)
                m.at(c, r) = static_cast<cthis_t>(this)->at(r, c);
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpTranspose<M, T, R, C, false> {};

}