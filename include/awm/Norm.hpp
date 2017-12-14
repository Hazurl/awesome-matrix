#pragma once

#include <awm/config.hpp>

namespace awm {

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // Is Noarm-able ?
    true
)>
class Norm {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = decltype(std::declval<T>() * std::declval<T>() + std::declval<T>() * std::declval<T>());
public:

    auto norm(int p = 2) const {
        return magnitude(type);
    }

    result_t magnitude(int p = 2) const {
            return std::pow(std::accumulate(begin(), end(), T{}, [p] (cr_value acc, cr_value m) { return acc + std::pow(m, p); }), 1./p);
    }

    result_t order_of_magnitude(int p = 2) const {
        return std::accumulate(begin(), end(), T{}, [p] (cr_value acc, cr_value m) { return acc + std::pow(m, p); });
    }

    Matrix<T, R, C> normalized(int p = 2) const {
        Matrix<T, R, C> m;
        auto mag = magnitude(p);
        std::transform(begin(), end(), m.begin(), [mag] (cr_value t) { return t / mag; });
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class Norm<M, T, R, C, false> {};

}