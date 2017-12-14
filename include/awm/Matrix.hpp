#pragma once

#include <awm/config.hpp>

// Operations
#include <awm/Transposable.hpp>
#include <awm/RowsOperations.hpp>
#include <awm/ColumnsOperations.hpp>
#include <awm/SubMatrix.hpp>
#include <awm/Determinant.hpp>
#include <awm/Square.hpp>

#include <numeric>
#include <algorithm>
#include <cmath>
#include <initializer_list>

namespace awm {

template<typename T, uint R, uint C, bool use_const_ref_not_value_copy = (sizeof(T) > 8)>
class Matrix :
    public Transposable         <Matrix, T, R, C>,
    public SwitchableRows       <Matrix, T, R, C>,
    public DeletableRow         <Matrix, T, R, C>,
    public ExtractableRow       <Matrix, T, R, C>,
    public MultiplyRow          <Matrix, T, R, C>,
    public SwitchableColumns    <Matrix, T, R, C>,
    public DeletableColumn      <Matrix, T, R, C>,
    public ExtractableColumn    <Matrix, T, R, C>,
    public MultiplyColumn       <Matrix, T, R, C>,
    public SubMatrix            <Matrix, T, R, C>,
    public Square               <Matrix, T, R, C>,
    public Determinant          <Matrix, T, R, C>,
    public Without              <Matrix, T, R, C>
{
    static_assert((R*C) != 0, "Matrix must have at least one value");

    using precision_float_type = 
#ifdef AWM_DOUBLE_PRECISION
        double;
#else
        float;
#endif

    using cr_value = std::conditional_t<use_const_ref_not_value_copy, const T&, T>;

    struct Row {
    private:
        Matrix<T, R, C>* mat;
        uint r;
        bool on_heap = false;

        friend Matrix<T, R, C>;

        Row(Matrix<T, R, C>& mat, uint r) : mat(&mat), r(r) {}
        Row(Matrix<T, R, C> const& mat, uint r) : mat(new Matrix<T, R, C>(mat)), r(r), on_heap(true) {}

    public:
        ~Row() { if (on_heap) delete mat; }

        T& operator [](uint c) {
            return mat->at(r, c);
        }

        cr_value operator [](uint c) const {
            return mat->at(r, c);
        }

        operator Matrix<T, 1, C> () {
            Matrix<T, 1, C> m;
            for(int i = 0; i < C; ++i)
                m.at(0, i) = (*this)[i];
            return m;
        }

    };

    struct CRow {
    private:
        Matrix<T, R, C> const* mat;
        uint r;

        friend Matrix<T, R, C>;

        CRow(Matrix<T, R, C> const& mat, uint r) : mat(&mat), r(r) {}
    public:

        cr_value operator [](uint c) const {
            return mat->at(r, c);
        }

        operator Matrix<T, 1, C> () {
            Matrix<T, 1, C> m;
            for(int i = 0; i < C; ++i)
                m.at(0, i) = (*this)[i];
            return m;
        }

    };
public:

    Matrix() {}
    Matrix(T initial) {
        std::fill(begin(), end(), initial);
    }
    Matrix(std::initializer_list<T> const& i) {
        std::copy(std::begin(i), std::end(i), begin());
    }
    Matrix(const T* a) {
        read_from(a);
    }

    constexpr uint row   () const { return R; }
    constexpr uint column() const { return C; }
    constexpr uint size  () const { return R*C; }

    T&       at(uint r, uint c) &        { return mat[r*C + c]; }
    cr_value at(uint r, uint c) const &  { return mat[r*C + c]; }
    T        at(uint r, uint c) const && { return mat[r*C + c]; }

    T* data () &            { return mat; }
    const T* data () const& { return mat; }

    Row operator [] (uint r) &  { return Row(*this, r); }
    Row operator [] (uint r) const && { return Row(*this, r); }
    CRow operator [] (uint r) const &  { return CRow(*this, r); }

    auto begin()            { return std::begin(mat); }
    auto begin() const      { return std::begin(mat); }
    auto cbegin() const     { return std::cbegin(mat); }
    auto rbegin()           { return std::rbegin(mat); }
    auto rbegin() const     { return std::rbegin(mat); }
    auto crbegin() const    { return std::crbegin(mat); }

    auto end()              { return std::end(mat); }
    auto end() const        { return std::end(mat); }
    auto cend() const       { return std::cend(mat); }
    auto rend()             { return std::rend(mat); }
    auto rend() const       { return std::rend(mat); }
    auto crend() const      { return std::crend(mat); }

    precision_float_type magnitude_square() const {
        return std::accumulate(std::begin(mat), std::end(mat), 0, [] (cr_value acc, cr_value m) { return acc + m * m; });
    }

    precision_float_type magnitude() const {
        return std::sqrt(magnitude_square());
    }

    Matrix<T, R, C> normalized() const {
        Matrix<T, R, C> m;
        auto mag = magnitude();
        std::transform(std::begin(mat), std::end(mat), std::begin(m.mat), [mag] (cr_value t) { return t / mag; });
        return m;
    }

    void read_from(const T* a) {
        std::copy(a, a + R*C, begin());
    }

    void write_to(T* a) const {
        std::copy(begin(), end(), a);
    }

private:
    T mat [R * C];
};

/* Operations */
/* Multiplication */

// M * M
template<typename T, uint R, uint C, uint X>
Matrix<T, R, C> operator * (Matrix<T, R, X> const& m, Matrix<T, X, C> const& n) {
    Matrix<T, R, C> o;
    for(uint r = 0; r < R; ++r)
        for(uint c = 0; c < C; ++c)
            for(uint k = 0; k < X; ++k)
                o.at(r, c) += m.at(r, k) * n.at(k, c);
    return o;
}

// M * T
template<typename T, uint R, uint C>
Matrix<T, R, C> operator * (Matrix<T, R, C> const& m, typename Matrix<T, R, C>::cr_value s) {
    Matrix<T, R, C> n;
    std::transform(m.begin(), m.end(), n.begin(), [&s] (typename Matrix<T, R, C>::cr_value v) { return v * s; });
    return n;
}

// T * M
template<typename T, uint R, uint C>
Matrix<T, R, C> operator * (typename Matrix<T, R, C>::cr_value s, Matrix<T, R, C> const& m) {
    return m * s;
}

/* Addition */

// M + M
template<typename T, uint R, uint C>
Matrix<T, R, C> operator + (Matrix<T, R, C> const& m, Matrix<T, R, C> const& n) {
    Matrix<T, R, C> o;
    std::transform(m.begin(), m.end(), n.begin(), o.begin(), [] (typename Matrix<T, R, C>::cr_value mv, typename Matrix<T, R, C>::cr_value nv) { return mv + nv; });
    return o;
}

// M + T
template<typename T, uint R, uint C>
Matrix<T, R, C> operator + (Matrix<T, R, C> const& m, typename Matrix<T, R, C>::cr_value s) {
    Matrix<T, R, C> n;
    std::transform(m.begin(), m.end(), n.begin(), [&s] (typename Matrix<T, R, C>::cr_value v) { return v + s; });
    return n;
}

// T + M
template<typename T, uint R, uint C>
Matrix<T, R, C> operator + (typename Matrix<T, R, C>::cr_value s, Matrix<T, R, C> const& m) {
    return m + s;
}

// +M
template<typename T, uint R, uint C>
Matrix<T, R, C> operator + (Matrix<T, R, C> const& m) {
    Matrix<T, R, C> o;
    std::transform(m.begin(), m.end(), o.begin(), [] (typename Matrix<T, R, C>::cr_value mv) { return +mv; });
    return o;
}

/* Substraction */

// M - M
template<typename T, uint R, uint C>
Matrix<T, R, C> operator - (Matrix<T, R, C> const& m, Matrix<T, R, C> const& n) {
    Matrix<T, R, C> o;
    std::transform(m.begin(), m.end(), n.begin(), o.begin(), [] (typename Matrix<T, R, C>::cr_value mv, typename Matrix<T, R, C>::cr_value nv) { return mv - nv; });
    return o;
}

// M - T
template<typename T, uint R, uint C>
Matrix<T, R, C> operator - (Matrix<T, R, C> const& m, typename Matrix<T, R, C>::cr_value s) {
    Matrix<T, R, C> n;
    std::transform(m.begin(), m.end(), n.begin(), [&s] (typename Matrix<T, R, C>::cr_value v) { return v - s; });
    return n;
}

// T - M
template<typename T, uint R, uint C>
Matrix<T, R, C> operator - (typename Matrix<T, R, C>::cr_value s, Matrix<T, R, C> const& m) {
    return m - s;
}

// -M
template<typename T, uint R, uint C>
Matrix<T, R, C> operator - (Matrix<T, R, C> const& m) {
    Matrix<T, R, C> o;
    std::transform(m.begin(), m.end(), o.begin(), [] (typename Matrix<T, R, C>::cr_value mv) { return -mv; });
    return o;
}

}