#pragma once

#include <awm/config.hpp>

namespace awm {

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // Has a determinant ?
    R == C
)>
class Determinant {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using factor_t = decltype(
        std::declval<int>() * std::declval<T>() * std::declval<decltype(
            std::declval<decltype(std::declval<Determinant<M, T, R-1, C-1>>())>().determinant()
        )>());
    using result_t = decltype(std::declval<factor_t>() + std::declval<factor_t>());
public:

    result_t determinant() const {
        result_t result{};
        for(uint i = 0; i < R; ++i) {
            auto sub = static_cast<cthis_t>(this)->delete_row(0).delete_column(i);
            result += (i%2 == 0? 1 : -1) * static_cast<cthis_t>(this)->at(0, i) * sub.determinant();
        }
        return result;
    }
};

template<template<typename, uint, uint> typename M, typename T>
class Determinant<M, T, 1, 1, true> {
    using this_t = M<T, 1, 1>*;
    using cthis_t = const M<T, 1, 1>*;
public:

    T determinant() const {
        return static_cast<cthis_t>(this)->at(0, 0);
    }
};

template<template<typename, uint, uint> typename M, typename T>
class Determinant<M, T, 2, 2, true> {
    using this_t = M<T, 2, 2>*;
    using cthis_t = const M<T, 2, 2>*;
public:

    auto determinant() const {
        return static_cast<cthis_t>(this)->at(0, 0) * 
               static_cast<cthis_t>(this)->at(1, 1) -
               static_cast<cthis_t>(this)->at(0, 1) *
               static_cast<cthis_t>(this)->at(1, 0);
    }
};

template<template<typename, uint, uint> typename M, typename T>
class Determinant<M, T, 3, 3, true> {
    using this_t = M<T, 3, 3>*;
    using cthis_t = const M<T, 3, 3>*;
public:

    auto determinant() const {
        return static_cast<cthis_t>(this)->at(0, 0) * static_cast<cthis_t>(this)->at(1, 1) * static_cast<cthis_t>(this)->at(2, 2)
             + static_cast<cthis_t>(this)->at(0, 1) * static_cast<cthis_t>(this)->at(1, 2) * static_cast<cthis_t>(this)->at(2, 0)
             + static_cast<cthis_t>(this)->at(0, 2) * static_cast<cthis_t>(this)->at(1, 0) * static_cast<cthis_t>(this)->at(2, 1)
             - static_cast<cthis_t>(this)->at(0, 0) * static_cast<cthis_t>(this)->at(1, 2) * static_cast<cthis_t>(this)->at(2, 1)
             - static_cast<cthis_t>(this)->at(0, 1) * static_cast<cthis_t>(this)->at(1, 0) * static_cast<cthis_t>(this)->at(2, 2)
             - static_cast<cthis_t>(this)->at(0, 2) * static_cast<cthis_t>(this)->at(1, 1) * static_cast<cthis_t>(this)->at(2, 0);
    }
};


template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class Determinant<M, T, R, C, false> {};

}