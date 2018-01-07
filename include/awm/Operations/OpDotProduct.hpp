#pragma once

#include <numeric>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    C == 1 || R == 1
)>
class OpDotProduct {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;

public:

    auto dot_product(M<T, R, C> const& v) const {
        return std::inner_product(v.begin(), v.end(), static_cast<cthis_t>(this)->begin(), T{});
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpDotProduct<M, T, R, C, false> {};

}