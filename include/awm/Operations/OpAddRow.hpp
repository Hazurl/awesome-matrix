#pragma once



#include <cassert>

namespace awm {

template<template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool = true>
class OpAddRow {
    using this_t = M<T, R, C>*;
    using cthis_t = const M<T, R, C>*;
    using result_t = M<T, R + 1, C>;
public:

    result_t add_column(unsigned int d, M<T, 1, C> const& row) const {
        assert(d <= R);
        
        if constexpr (R == 0) {
            return row;
        } else {
            result_t m;
            for(unsigned int r = 0; r < R; ++r) {
                for(unsigned int c = 0; c < C - 1; ++c)
                    m.at(r, c) = (
                        d == r ? // if this is the column `col` must be placed
                            // copy from the column
                            row.at(0, c)
                            // else copy from this, if the column has already been copied, subtract 1 to c to keep it in range [0, C[
                        :   static_cast<cthis_t>(this)->at(r >= d ? r - 1 : r, c)
                    );
            }
            return m;
        }
    }

};

}