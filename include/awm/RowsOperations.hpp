#pragma once

#include <awm/config.hpp>

#include <cassert>
#include <algorithm>

namespace awm {

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // rows are switchable ?
    true
)>
class SwitchableRows {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R, C>;
public:

    result_t switch_rows(uint r0, uint r1) const {
        assert(r0 < R && r1 < R);
        
        result_t m;
        for(uint r = 0; r < R; ++r) {
            if (r == r0)
                for(uint c = 0; c < C; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r1, c);
            else if (r == r1)
                for(uint c = 0; c < C; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r0, c);
            else
                for(uint c = 0; c < C; ++c)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c);
        }
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class SwitchableRows<M, T, R, C, false> {};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // rows are switchable ?
    R > 1
)>
class DeletableRow {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R - 1, C>;
public:

    result_t delete_row(uint d) const {
        assert(d < R);
        
        result_t m;
        for(uint r = 0; r < R - 1; ++r) {
            for(uint c = 0; c < C; ++c)
                m.at(r, c) = static_cast<cthis_t>(this)->at((r >= d ? r + 1 : r), c);
        }
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class DeletableRow<M, T, R, C, false> {};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // rows are extractable ?
    true
)>
class ExtractableRow {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, 1, C>;
public:

    result_t extract_row(uint rr) const {
        assert(rr < R);
        
        result_t m;
        for(uint c = 0; c < C; ++c)
            m.at(0, c) = static_cast<cthis_t>(this)->at(rr, c);
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class ExtractableRow<M, T, R, C, false> {};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C, bool = (
    // rows are multipliable ?
    true
)>
class MultiplyRow {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    template<typename TT>
    using result_t = M<TT, R, C>;
public:

    template<typename TT, typename TRes = decltype(std::declval<T>() * std::declval<TT>())>
    result_t<TRes> multiply_row(uint row, TT const& t) const {
        result_t<TRes> m; 
        for(uint r = 0; r < R; ++r) {
            for(uint c = 0; c < C; ++c) {
                if (r == row)
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c) * t;
                else
                    m.at(r, c) = static_cast<cthis_t>(this)->at(r, c);
            }
        }
        return m;
    }

};

template<template<typename, uint, uint> typename M, typename T, uint R, uint C>
class MultiplyRow<M, T, R, C, false> {};

}