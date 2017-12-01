#pragma once

#include <awm/config.hpp>

namespace awm {

template<typename T, uint R, uint C>
class Matrix {
    static_assert((R*C) != 0, "Matrix must have at least one value");
    struct Row {
    private:
        Matrix<T, R, C>& mat;
        uint r;
        friend Matrix<T, R, C>;
        Row(Matrix<T, R, C>& mat, uint r) : mat(mat), r(r) {}
    public:

        T& operator [](uint c) {
            return mat.at(r, c);
        }

        const T& operator [](uint c) const {
            return mat.at(r, c);
        }

    };
    struct CRow {
    private:
        Matrix<T, R, C> const& mat;
        uint r;
        friend Matrix<T, R, C>;
        CRow(Matrix<T, R, C> const& mat, uint r) : mat(mat), r(r) {}
    public:

        const T& operator [](uint c) const {
            return mat.at(r, c);
        }

    };
public:

    T& at(uint r, uint c) {
        return mat[r*C + c];
    }

    const T& at(uint r, uint c) const {
        return mat[r*C + c];
    }

    explicit operator T* () {
        return mat;
    }

    explicit operator const T* () const {
        return mat;
    }

    Row operator [] (uint r) {
        return Row{*this, r};
    }

    CRow operator [] (uint r) const {
        return Row{*this, r};
    }

private:
    T mat [R * C];
};

}