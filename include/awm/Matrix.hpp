#pragma once

#include <awm/config.hpp>

#include <awm/MatrixData.hpp>

// Operations
#include <awm/Transposable.hpp>
#include <awm/RowsOperations.hpp>
#include <awm/ColumnsOperations.hpp>
#include <awm/SubMatrix.hpp>
#include <awm/Determinant.hpp>
#include <awm/Square.hpp>
#include <awm/Norm.hpp>

#include <numeric>
#include <algorithm>
#include <cmath>
#include <initializer_list>

namespace awm {

template<typename T, uint R, uint C>
class Matrix :
    public MatrixData           <        T, R, C>,
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
    public Adjugate             <Matrix, T, R, C>,
    public Inverse              <Matrix, T, R, C>,
    public Cofactors            <Matrix, T, R, C>,
    public Without              <Matrix, T, R, C>,
    public Norm                 <Matrix, T, R, C>
{

public:
    using cr_value = std::conditional_t<(sizeof(T) > 8), const T&, T>;

private:
    struct Row {
    private:
        Matrix<T, R, C>* mat;
        uint r;
        bool on_heap = false;

        friend Matrix<T, R, C>;

        Row(Matrix<T, R, C>& mat, uint r) : mat(&mat), r(r) {}
        Row(Matrix<T, R, C> const& mat, uint r) : mat(new Matrix<T, R, C>(mat)), r(r), on_heap(true) {}

    public:
        Row(Row const& row) : Row(*row.mat, row.r) {}
        Row(Row&& row) : Row(*row.mat, row.r) { row.on_heap = false; }
        Row& operator = (Row row) { if (on_heap) delete mat; mat = std::move(row.mat); r = std::move(mat.r); on_heap = row.on_heap; row.on_heap = false;}
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
        const Matrix<T, R, C>* mat;
        uint r;

        friend Matrix<T, R, C>;

        CRow(Matrix<T, R, C> const& mat, uint r) : mat(&mat), r(r) {}
        CRow(Row const& row) : mat(row.mat), r(row.r) {}
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

    T&       at(uint r, uint c) &        { return this->pointer_data()[r*C + c]; }
    cr_value at(uint r, uint c) const &  { return this->pointer_data()[r*C + c]; }
    T        at(uint r, uint c) const && { return this->pointer_data()[r*C + c]; }

          T* data () &      { return this->pointer_data(); }
    const T* data () const& { return this->pointer_data(); }

    Row operator [] (uint r) &          { return Row(*this, r); }
    Row operator [] (uint r) const &&   { return Row(*this, r); }
    CRow operator [] (uint r) const &   { return CRow(*this, r); }

    auto begin()            { return this->pointer_data(); }
    auto begin() const      { return this->pointer_data(); }
    auto cbegin() const     { return this->pointer_data(); }
/* need a proper class
    auto rbegin()           { return std::rbegin(this->pointer_data()); }
    auto rbegin() const     { return std::rbegin(this->pointer_data()); }
    auto crbegin() const    { return std::crbegin(this->pointer_data()); }
*/
    auto end()              { return this->pointer_data_end(); }
    auto end() const        { return this->pointer_data_end(); }
    auto cend() const       { return this->pointer_data_end(); }
/*
    auto rend()             { return std::rend(this->pointer_data()); }
    auto rend() const       { return std::rend(this->pointer_data()); }
    auto crend() const      { return std::crend(this->pointer_data()); }
*/
    void read_from(const T* a) {
        std::copy(a, a + R*C, begin());
    }

    void write_to(T* a) const {
        std::copy(begin(), end(), a);
    }
};

/* Operations */
/* Multiplication */

// M * M
template<typename T, uint R, uint C, uint X>
Matrix<T, R, C> operator * (Matrix<T, R, X> const& m, Matrix<T, X, C> const& n) {
    Matrix<T, R, C> o(T{});
    for(uint r = 0; r < R; ++r)
        for(uint c = 0; c < C; ++c)
            for(uint k = 0; k < X; ++k)
                o.at(r, c) += m.at(r, k) * n.at(k, c);
    return o;
}

// M * T
template<typename TT, typename T, uint R, uint C>
Matrix<T, R, C> operator * (Matrix<T, R, C> const& m, TT const& s) {
    Matrix<T, R, C> n;
    std::transform(m.begin(), m.end(), n.begin(), [&s] (typename Matrix<T, R, C>::cr_value v) { return v * s; });
    return n;
}

// T * M
template<typename TT, typename T, uint R, uint C>
Matrix<T, R, C> operator * (TT const& s, Matrix<T, R, C> const& m) {
    return m * s;
}

/* Division */

// M / T
template<typename TT, typename T, uint R, uint C>
Matrix<T, R, C> operator / (Matrix<T, R, C> const& m, TT const& s) {
    Matrix<T, R, C> n;
    std::transform(m.begin(), m.end(), n.begin(), [&s] (typename Matrix<T, R, C>::cr_value v) { return v / s; });
    return n;
}

// T / M
template<typename TT, typename T, uint R, uint C>
Matrix<T, R, C> operator / (TT const& s, Matrix<T, R, C> const& m) {
    return m / s;
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
template<typename TT, typename T, uint R, uint C>
Matrix<T, R, C> operator + (Matrix<T, R, C> const& m, TT const& s) {
    Matrix<T, R, C> n;
    std::transform(m.begin(), m.end(), n.begin(), [&s] (typename Matrix<T, R, C>::cr_value v) { return v + s; });
    return n;
}

// T + M
template<typename TT, typename T, uint R, uint C>
Matrix<T, R, C> operator + (TT const& s, Matrix<T, R, C> const& m) {
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
template<typename TT, typename T, uint R, uint C>
Matrix<T, R, C> operator - (Matrix<T, R, C> const& m, TT const& s) {
    Matrix<T, R, C> n;
    std::transform(m.begin(), m.end(), n.begin(), [&s] (typename Matrix<T, R, C>::cr_value v) { return v - s; });
    return n;
}

// T - M
template<typename TT, typename T, uint R, uint C>
Matrix<T, R, C> operator - (TT const& s, Matrix<T, R, C> const& m) {
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