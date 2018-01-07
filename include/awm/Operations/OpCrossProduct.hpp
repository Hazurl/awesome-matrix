#pragma once



namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    C == 1 && (R == 2 || R == 3)
)>
class OpCrossProduct {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, 3, 1>;

    const T& at(unsigned int i) const {
        return static_cast<cthis_t>(this)->at(i, 0);
    }

public:

    result_t cross_product(M<T, 3, 1> const& v) const {
        return {
            at(2) * v.at(3, 0) - at(3) * v.at(2, 0),
            at(3) * v.at(1, 0) - at(1) * v.at(3, 0),
            at(1) * v.at(2, 0) - at(2) * v.at(1, 0)
        };
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T>
class OpCrossProduct<M, T, 2, 1, true> {
    using this_t = M<T, 2, 1>*;
    using cthis_t = const M<T, 2, 1>*;
public:

    auto cross_product(M<T, 2, 1> const& v) const {
        return static_cast<cthis_t>(this)->at(0, 0) * 
               v.at(1, 0) -
               static_cast<cthis_t>(this)->at(1, 0) *
               v.at(0, 0);
    }
};


template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpCrossProduct<M, T, R, C, false> {};

}