#pragma once

#include <awm/config.hpp>

#include <cassert>
#include <algorithm>

namespace awm {

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // columns are switchable ?
    true
)>
class SwitchableColumns {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R, C>;
public:

    result_t switch_columns(uint c0, uint c1) const {
        assert(c0 < C && c1 < C);
        
        result_t m;
        for(uint c = 0; c < C; ++c) {
            if (c == c0)
                for(uint r = 0; r < R; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c1);
            else if (c == c1)
                for(uint r = 0; r < R; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c0);
            else
                for(uint r = 0; r < R; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c);
        }
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class SwitchableColumns<M, T, R, C, false> {};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // columns are switchable ?
    C > 1
)>
class DeletableColumn {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R, C - 1>;
public:

    result_t delete_column(uint d) const {
        assert(d < C);
        
        result_t m;
        for(uint r = 0; r < R; ++r) {
            for(uint c = 0; c < C - 1; ++c)
                m.at(r, c) = static_cast<cthis_t>(this)->at(r, (c >= d ? c + 1 : c));
        }
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class DeletableColumn<M, T, R, C, false> {};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // columns are extractable ?
    true
)>
class ExtractableColumn {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R, 1>;
public:

    result_t extract_column(uint cc) const {
        assert(cc < C);
        
        result_t m;
        for(uint r = 0; r < R; ++r)
            m.at(r, 0) = static_cast<cthis_t>(this)->at(r, cc);
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class ExtractableColumn<M, T, R, C, false> {};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // columns are multipliable ?
    true
)>
class MultiplyColumn {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    template<typename TT>
    using result_t = M<TT, R, C>;
public:

    template<typename TT, typename TRes = decltype(std::declval<T>() * std::declval<TT>())>
    result_t<TRes> multiply_column(uint col, TT const& t) const {
        result_t<TRes> m; 
        for(uint r = 0; r < R; ++r) {
            for(uint c = 0; c < C; ++c) {
                if (c == col)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c) * t;
                else
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c);
            }
        }
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class MultiplyColumn<M, T, R, C, false> {};

}