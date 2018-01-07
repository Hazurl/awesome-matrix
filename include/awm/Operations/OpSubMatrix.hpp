#pragma once



namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    true
)>
class OpSubMatrix {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
public:

    template<unsigned int RR, unsigned int CC>
    M<T, RR, CC> submatrix(unsigned int r0, unsigned int c0) const {
        M<T, RR, CC> m;
        for(unsigned int r = r0; r < r0+RR; ++r)
            for(unsigned int c = c0; c < c0+CC; ++c)
                m.at(r-r0, c-c0) = static_cast<cthis_t>(this)->at(r, c);
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpSubMatrix<M, T, R, C, false> {};


}