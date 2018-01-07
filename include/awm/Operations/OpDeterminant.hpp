#pragma once



namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    R == C
)>
class OpDeterminant {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using factor_t = decltype(
        std::declval<int>() * std::declval<T>() * std::declval<decltype(
            std::declval<decltype(std::declval<OpDeterminant<M, T, R-1, C-1>>())>().determinant()
        )>());
    using result_t = decltype(std::declval<factor_t>() + std::declval<factor_t>());
public:

    result_t determinant() const {
        result_t result{};
        for(unsigned int i = 0; i < R; ++i) {
            auto sub = static_cast<cthis_t>(this)->without(0, i);
            result += (i%2 == 0? 1 : -1) * static_cast<cthis_t>(this)->at(0, i) * sub.determinant();
        }
        return result;
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T>
class OpDeterminant<M, T, 0, 0, true> {
    using this_t = M<T, 0, 0>*;
    using cthis_t = const M<T, 0, 0>*;
public:

    T determinant() const {
        return 1;
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T>
class OpDeterminant<M, T, 1, 1, true> {
    using this_t = M<T, 1, 1>*;
    using cthis_t = const M<T, 1, 1>*;
public:

    T determinant() const {
        return static_cast<cthis_t>(this)->at(0, 0);
    }
};

template<template<typename, unsigned int, unsigned int> typename M, typename T>
class OpDeterminant<M, T, 2, 2, true> {
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

template<template<typename, unsigned int, unsigned int> typename M, typename T>
class OpDeterminant<M, T, 3, 3, true> {
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


template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpDeterminant<M, T, R, C, false> {};

}