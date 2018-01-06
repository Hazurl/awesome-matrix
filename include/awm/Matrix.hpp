#pragma once

#include <awm/MatrixData.hpp>

// Operations
#include <awm/Operations/OpDeleteColumn.hpp>
#include <awm/Operations/OpExtractColumn.hpp>
#include <awm/Operations/OpMultiplyColumn.hpp>
#include <awm/Operations/OpSwitchColumn.hpp>

#include <awm/Operations/OpDeleteRow.hpp>
#include <awm/Operations/OpExtractRow.hpp>
#include <awm/Operations/OpMultiplyRow.hpp>
#include <awm/Operations/OpSwitchRow.hpp>

#include <awm/Operations/OpTranspose.hpp>

#include <awm/Operations/OpAdjugate.hpp>
#include <awm/Operations/OpCofactors.hpp>
#include <awm/Operations/OpDeterminant.hpp>
#include <awm/Operations/OpInverse.hpp>
#include <awm/Operations/OpMinors.hpp>

#include <awm/Operations/OpSubMatrix.hpp>
#include <awm/Operations/OpWithout.hpp>

#include <awm/Constructor/CtorDiagonal.hpp>
#include <awm/Constructor/CtorIdentity.hpp>

#include <awm/Operations/OpIsTriangle.hpp>
#include <awm/Operations/OpIsDiagonal.hpp>

#include <awm/Iterators.hpp>

#include <numeric>
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <sstream>
#include <stdexcept>

namespace awm {

template<typename T, unsigned int R, unsigned int C>
class Matrix;

/* Alias */

// Matrix
template<unsigned int R, unsigned int C>
using Matrixf = Matrix<float, R, C>;
template<unsigned int R, unsigned int C>
using Matrixd = Matrix<double, R, C>;

template<typename T>
using Matrix4 = Matrix<T, 4, 4>;
template<typename T>
using Matrix3 = Matrix<T, 3, 3>;
template<typename T>
using Matrix2 = Matrix<T, 2, 2>;

using Matrix4f = Matrix4<float>;
using Matrix3f = Matrix3<float>;
using Matrix2f = Matrix2<float>;

using Matrix4d = Matrix4<double>;
using Matrix3d = Matrix3<double>;
using Matrix2d = Matrix2<double>;

// Vector
template<typename T, unsigned int S>
using Vector = Matrix<T, S, 1>;

template<typename T>
using Vector4 = Vector<T, 4>;
template<typename T>
using Vector3 = Vector<T, 3>;
template<typename T>
using Vector2 = Vector<T, 2>;

template<unsigned int S>
using Vectorf = Vector<float, S>;
template<unsigned int S>
using Vectord = Vector<double, S>;

using Vector4f = Vectorf<4>;
using Vector3f = Vectorf<3>;
using Vector2f = Vectorf<2>;

using Vector4d = Vectord<4>;
using Vector3d = Vectord<3>;
using Vector2d = Vectord<2>;

/* Matrix */

template<typename T, unsigned int R, unsigned int C>
class Matrix :
    public MatrixData           <        T, R, C>,

    public OpTranspose          <Matrix, T, R, C>,

    public OpDeleteColumn       <Matrix, T, R, C>,
    public OpSwitchColumn       <Matrix, T, R, C>,
    public OpMultiplyColumn     <Matrix, T, R, C>,
    public OpExtractColumn      <Matrix, T, R, C>,

    public OpDeleteRow          <Matrix, T, R, C>,
    public OpSwitchRow          <Matrix, T, R, C>,
    public OpMultiplyRow        <Matrix, T, R, C>,
    public OpExtractRow         <Matrix, T, R, C>,

    public OpSubMatrix          <Matrix, T, R, C>,
    public OpWithout            <Matrix, T, R, C>,

    public OpDeterminant        <Matrix, T, R, C>,
    public OpCofactors          <Matrix, T, R, C>,
    public OpMinors             <Matrix, T, R, C>,
    public OpAdjugate           <Matrix, T, R, C>,
    public OpInverse            <Matrix, T, R, C>,

    public OpIsDiagonal         <Matrix, T, R, C>,
    public OpIsTriangle         <Matrix, T, R, C>,

    public CtorDiagonal         <Matrix, T, R, C>,
    public CtorIdentity         <Matrix, T, R, C>

{

public:
    using this_t = Matrix<T, R, C>;
    using container_t = this_t;

    using cr_value = std::conditional_t<(sizeof(T) > 8), const T&, T>;

    using forward_iterator = RandomIterator<container_t, T, true>;
    using backward_iterator = RandomIterator<container_t, T, false>;
    using forward_const_iterator = ConstRandomIterator<container_t, T, true>;
    using backward_const_iterator = ConstRandomIterator<container_t, T, false>;

private:
    struct Row {
    private:
        Matrix<T, R, C>* mat;
        unsigned int r;
        bool on_heap = false;

        friend Matrix<T, R, C>;

        Row(Matrix<T, R, C>& mat, unsigned int r) : mat(&mat), r(r) {}
        Row(Matrix<T, R, C> const& mat, unsigned int r) : mat(new Matrix<T, R, C>(mat)), r(r), on_heap(true) {}

    public:
        Row(Row const& row) : Row(*row.mat, row.r) {}
        Row(Row&& row) : Row(*row.mat, row.r) { row.on_heap = false; }
        Row& operator = (Row row) { if (on_heap) delete mat; mat = std::move(row.mat); r = std::move(mat.r); on_heap = row.on_heap; row.on_heap = false;}
        ~Row() { if (on_heap) delete mat; }

        T& operator [](unsigned int c) {
            return (*mat)(r, c);
        }

        cr_value operator [](unsigned int c) const {
            return (*mat)(r, c);
        }

        T& at (unsigned int c) {
            if (c < C)
                return (*this)[c];
            throw std::out_of_range("Either row or column is out of range");
        }

        cr_value at (unsigned int c) const {
            if (c < C)
                return (*this)[c];
            throw std::out_of_range("Either row or column is out of range");
        }

        operator Matrix<T, 1, C> () {
            Matrix<T, 1, C> m;
            for(int i = 0; i < C; ++i)
                (*m)(0, i) = (*this)[i];
            return m;
        }

    };

    struct CRow {
    private:
        const Matrix<T, R, C>* mat;
        unsigned int r;

        friend Matrix<T, R, C>;

        CRow(Matrix<T, R, C> const& mat, unsigned int r) : mat(&mat), r(r) {}
        CRow(Row const& row) : mat(row.mat), r(row.r) {}
    public:

        cr_value operator [](unsigned int c) const {
            return mat(r, c);
        }

        cr_value at (unsigned int c) const {
            if (c < C)
                return (*this)[c];
            throw std::out_of_range("Either row or column is out of range");
        }

        operator Matrix<T, 1, C> () {
            Matrix<T, 1, C> m;
            for(int i = 0; i < C; ++i)
                m(0, i) = (*this)[i];
            return m;
        }

    };

    constexpr unsigned int index_of(unsigned int r, unsigned int c) const { return column() * r + c; } 

public:

    Matrix() {}
    Matrix(cr_value initial) {
        std::fill(begin(), end(), initial);
    }
    Matrix(std::initializer_list<T> const& i) {
        std::copy(std::begin(i), std::end(i), begin());
    }
    Matrix(const T* a) {
        read_from(a);
    }

    constexpr unsigned int row   () const { return R; }
    constexpr unsigned int column() const { return C; }
    constexpr unsigned int size  () const { return row() * column(); }
    constexpr bool is_square() const { return row() == column(); } 
    constexpr bool in_range(unsigned int r, unsigned int c) const { return r < row() && c < column(); }

    T&       at(unsigned int r, unsigned int c) &        { if (in_range(r, c)) return this->pointer_data()[index_of(r, c)]; throw std::out_of_range("Either row or column is out of range"); }
    T const& at(unsigned int r, unsigned int c) const &  { if (in_range(r, c)) return this->pointer_data()[index_of(r, c)]; throw std::out_of_range("Either row or column is out of range"); }
    T        at(unsigned int r, unsigned int c) const && { if (in_range(r, c)) return this->pointer_data()[index_of(r, c)]; throw std::out_of_range("Either row or column is out of range"); }

    T&       operator () (unsigned int r, unsigned int c) &        { return this->pointer_data()[index_of(r, c)]; }
    T const& operator () (unsigned int r, unsigned int c) const &  { return this->pointer_data()[index_of(r, c)]; }
    T        operator () (unsigned int r, unsigned int c) const && { return this->pointer_data()[index_of(r, c)]; }

          T* data () &      { return this->pointer_data(); }
    const T* data () const& { return this->pointer_data(); }

    Row operator [] (unsigned int r) &          { return Row(*this, r); }
    Row operator [] (unsigned int r) const &&   { return Row(*this, r); }
    CRow operator [] (unsigned int r) const &   { return CRow(*this, r); }

    void read_from(const T* a) {
        std::copy(a, a + size(), begin());
    }

    void write_to(T* a) const {
        std::copy(begin(), end(), a);
    }

    auto begin()  { return forward_iterator(*this, 0); }
    auto end()    { return forward_iterator(*this, size()); }
    auto rbegin() { return backward_iterator(*this, 0); }
    auto rend()   { return backward_iterator(*this, size()); }

    auto cbegin() const   { return forward_const_iterator(*this, 0); }
    auto cend() const     { return forward_const_iterator(*this, size()); }
    auto crbegin() const  { return backward_const_iterator(*this, 0); }
    auto crend() const    { return backward_const_iterator(*this, size()); }

    auto begin() const   { return cbegin(); }
    auto end() const     { return cend(); }
    auto rbegin() const  { return crbegin(); }
    auto rend() const    { return crend(); }

    auto iterator_to(unsigned int r, unsigned int c) { return forward_iterator(*this, index_of(r, c)); }
    auto citerator_to(unsigned int r, unsigned int c) { return forward_const_iterator(*this, index_of(r, c)); }
    auto riterator_to(unsigned int r, unsigned int c) { return backward_iterator(*this, size() - 1 - index_of(r, c)); }
    auto criterator_to(unsigned int r, unsigned int c) { return backward_const_iterator(*this, size() - 1 - index_of(r, c)); }

    template<typename I>
    // { Row, Column }
    std::pair<unsigned int, unsigned int> get_indices(I const& it) const {
        return { (it.pos - it.pos % column()) / column() , it.pos % column() };
    }

    auto norm(int p = 2) const {
        return magnitude(p);
    }

    auto magnitude(int p = 2) const {
        return std::pow(std::accumulate(begin(), end(), T{}, 
            [p] (cr_value acc, cr_value m) { return acc + std::pow(m, p); }), 1./p);
    }

    auto power_of_magnitude(int p = 2) const {
        return std::accumulate(begin(), end(), T{}, 
            [p] (cr_value acc, cr_value m) { return acc + std::pow(m, p); });
    }

    auto normalized(int p = 2) const {
        Matrix<T, R, C> m;
        auto mag = magnitude(p);
        std::transform(begin(), end(), m.begin(), 
            [mag] (cr_value t) { return t / mag; });
        return m;
    }


};

/* Operations */
/* Multiplication */

// M * M
template<typename T, unsigned int R, unsigned int C, unsigned int X>
Matrix<T, R, C> operator * (Matrix<T, R, X> const& m, Matrix<T, X, C> const& n) {
    Matrix<T, R, C> o(T{});
    for(unsigned int r = 0; r < R; ++r)
        for(unsigned int c = 0; c < C; ++c)
            for(unsigned int k = 0; k < X; ++k)
                o(r, c) += m(r, k) * n(k, c);
    return o;
}

// M * T
template<typename TT, typename T, unsigned int R, unsigned int C>
Matrix<T, R, C> operator * (Matrix<T, R, C> const& m, TT const& s) {
    Matrix<T, R, C> n;
    std::transform(m.begin(), m.end(), n.begin(), [&s] (typename Matrix<T, R, C>::cr_value v) { return v * s; });
    return n;
}

// T * M
template<typename TT, typename T, unsigned int R, unsigned int C>
Matrix<T, R, C> operator * (TT const& s, Matrix<T, R, C> const& m) {
    return m * s;
}

/* Division */

// M / T
template<typename TT, typename T, unsigned int R, unsigned int C>
Matrix<T, R, C> operator / (Matrix<T, R, C> const& m, TT const& s) {
    Matrix<T, R, C> n;
    std::transform(m.begin(), m.end(), n.begin(), [&s] (typename Matrix<T, R, C>::cr_value v) { return v / s; });
    return n;
}

// T / M
template<typename TT, typename T, unsigned int R, unsigned int C>
Matrix<T, R, C> operator / (TT const& s, Matrix<T, R, C> const& m) {
    return m / s;
}

/* Addition */

// M + M
template<typename T, unsigned int R, unsigned int C>
Matrix<T, R, C> operator + (Matrix<T, R, C> const& m, Matrix<T, R, C> const& n) {
    Matrix<T, R, C> o;
    std::transform(m.begin(), m.end(), n.begin(), o.begin(), [] (typename Matrix<T, R, C>::cr_value mv, typename Matrix<T, R, C>::cr_value nv) { return mv + nv; });
    return o;
}

// +M
template<typename T, unsigned int R, unsigned int C>
Matrix<T, R, C> operator + (Matrix<T, R, C> const& m) {
    Matrix<T, R, C> o;
    std::transform(m.begin(), m.end(), o.begin(), [] (typename Matrix<T, R, C>::cr_value mv) { return +mv; });
    return o;
}

/* Substraction */

// M - M
template<typename T, unsigned int R, unsigned int C>
Matrix<T, R, C> operator - (Matrix<T, R, C> const& m, Matrix<T, R, C> const& n) {
    Matrix<T, R, C> o;
    std::transform(m.begin(), m.end(), n.begin(), o.begin(), [] (typename Matrix<T, R, C>::cr_value mv, typename Matrix<T, R, C>::cr_value nv) { return mv - nv; });
    return o;
}

// -M
template<typename T, unsigned int R, unsigned int C>
Matrix<T, R, C> operator - (Matrix<T, R, C> const& m) {
    Matrix<T, R, C> o;
    std::transform(m.begin(), m.end(), o.begin(), [] (typename Matrix<T, R, C>::cr_value mv) { return -mv; });
    return o;
}

/* Stream */

template<typename T, unsigned int R, unsigned int C>
std::ostream& operator << (std::ostream& os, Matrix<T, R, C> const& m) {
    if (R == 0) 
        return os << "[]\n";

    unsigned int size = 0;
    for (unsigned int r = 0; r < R; r++) {
        for(unsigned int c = 0; c < C ; ++c) {
            std::stringstream ss;
            ss << m(r, c) << " ";
            ss.seekg(0, std::ios::end);
            size = std::max(size, static_cast<unsigned int>(ss.tellg()));
        }
    }

    for (unsigned int r = 0; r < R; r++) {
        if (r == 0)
            os << (R == 1 ? "[ " : "┌ ");
        else if (r < R - 1)
            os << "│ ";
        else
            os << "└ ";
        for(unsigned int c = 0; c < C ; ++c) {
            std::stringstream ss;
            ss << m(r, c) << " ";
            ss.seekg(0, std::ios::end);
            unsigned int csize = ss.tellg();
            for(int i = size - csize; i > 0; --i)
                os << ' ';
            os << ss.str();
        }
        if (r == 0)
            os << (R == 1 ? "]\n" : "┐\n");
        else if (r < R-1)
            os << "│\n";
        else
            os << "┘\n";
    }
    return os;
}

}