#pragma once



namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = (
    C > 0
)>
class OpMultiplyColumn {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    template<typename TT>
    using result_t = M<TT, R, C>;
public:

    template<typename TT, typename TRes = decltype(std::declval<T>() * std::declval<TT>())>
    result_t<TRes> multiply_column(unsigned int col, TT const& t) const {
        result_t<TRes> m; 
        for(unsigned int r = 0; r < R; ++r) {
            for(unsigned int c = 0; c < C; ++c) {
                if (c == col)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c) * t;
                else
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c);
            }
        }
        return m;
    }

};

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C>
class OpMultiplyColumn<M, T, R, C, false> {};

}