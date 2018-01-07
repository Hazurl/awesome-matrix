#pragma once



namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    R == C
)>
class CtorIdentity {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R, C>;
    using cr_value = std::conditional_t<(sizeof(T) > 8), const T&, T>;
public:

    static result_t identity(cr_value value = 1) {
        result_t m(0);
        for(unsigned int i = 0; i < R; ++i) m.at(i, i) = value;
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class CtorIdentity<M, T, R, C, false> {};

}