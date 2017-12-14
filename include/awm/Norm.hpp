#pragma once

#include <awm/config.hpp>

#include <cmath>
#include <numeric>
#include <algorithm>

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
        return magnitude(p);
    }

    result_t magnitude(int p = 2) const {
            return std::pow(std::accumulate(static_cast<cthis_t>(this)->begin(), static_cast<cthis_t>(this)->end(), T{}, 
                [p] (T const& acc, T const& m) { return acc + std::pow(m, p); }), 1./p);
    }

    result_t order_of_magnitude(int p = 2) const {
        return std::accumulate(static_cast<cthis_t>(this)->begin(), static_cast<cthis_t>(this)->end(), T{}, [p] (T const& acc, T const& m) { return acc + std::pow(m, p); });
    }

    M<T, R, C> normalized(int p = 2) const {
        M<T, R, C> m;
        auto mag = magnitude(p);
        std::transform(static_cast<cthis_t>(this)->begin(), static_cast<cthis_t>(this)->end(), m.begin(), [mag] (T const& t) { return t / mag; });
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class Norm<M, T, R, C, false> {};

}