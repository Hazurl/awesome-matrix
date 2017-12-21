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
#include <sstream>
#include <stdexcept>

namespace awm {

template<typename T, uint R, uint C>
class Matrix;

/* Alias */

// Matrix
template<uint R, uint C>
using Matrixf = Matrix<float, R, C>;
template<uint R, uint C>
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
template<typename T, uint S>
using Vector = Matrix<T, S, 1>;

template<typename T>
using Vector4 = Vector<T, 4>;
template<typename T>
using Vector3 = Vector<T, 3>;
template<typename T>
using Vector2 = Vector<T, 2>;

template<uint S>
using Vectorf = Vector<float, S>;
template<uint S>
using Vectord = Vector<double, S>;

using Vector4f = Vectorf<4>;
using Vector3f = Vectorf<3>;
using Vector2f = Vectorf<2>;

using Vector4d = Vectord<4>;
using Vector3d = Vectord<3>;
using Vector2d = Vectord<2>;

/* Matrix */

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
            return (*mat)(r, c);
        }

        cr_value operator [](uint c) const {
            return (*mat)(r, c);
        }

        T& at (uint c) {
            if (c < C)
                return (*this)[c];
            throw std::out_of_range("Either row or column is out of range");
        }

        cr_value at (uint c) const {
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
        uint r;

        friend Matrix<T, R, C>;

        CRow(Matrix<T, R, C> const& mat, uint r) : mat(&mat), r(r) {}
        CRow(Row const& row) : mat(row.mat), r(row.r) {}
    public:

        cr_value operator [](uint c) const {
            return mat(r, c);
        }

        cr_value at (uint c) const {
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

    constexpr uint row   () const { return R; }
    constexpr uint column() const { return C; }
    constexpr uint size  () const { return R*C; }
    constexpr bool in_range(uint r, uint c) const { return r < row() && c < column(); }

    T&       at(uint r, uint c) &        { if (in_range(r, c)) return this->pointer_data()[r*C + c]; throw std::out_of_range("Either row or column is out of range"); }
    cr_value at(uint r, uint c) const &  { if (in_range(r, c)) return this->pointer_data()[r*C + c]; throw std::out_of_range("Either row or column is out of range"); }
    T        at(uint r, uint c) const && { if (in_range(r, c)) return this->pointer_data()[r*C + c]; throw std::out_of_range("Either row or column is out of range"); }

    T&       operator () (uint r, uint c) &        { return this->pointer_data()[r*C + c]; }
    cr_value operator () (uint r, uint c) const &  { return this->pointer_data()[r*C + c]; }
    T        operator () (uint r, uint c) const && { return this->pointer_data()[r*C + c]; }

          T* data () &      { return this->pointer_data(); }
    const T* data () const& { return this->pointer_data(); }

    Row operator [] (uint r) &          { return Row(*this, r); }
    Row operator [] (uint r) const &&   { return Row(*this, r); }
    CRow operator [] (uint r) const &   { return CRow(*this, r); }

    void read_from(const T* a) {
        std::copy(a, a + R*C, begin());
    }

    void write_to(T* a) const {
        std::copy(begin(), end(), a);
    }

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
                o(r, c) += m(r, k) * n(k, c);
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

/* Stream */

template<typename T, uint R, uint C>
std::ostream& operator << (std::ostream& os, Matrix<T, R, C> const& m) {
    if (R == 0) 
        return os << "[]\n";

    uint size = 0;
    for (uint r = 0; r < R; r++) {
        for(uint c = 0; c < C ; ++c) {
            std::stringstream ss;
            ss << m(r, c) << " ";
            ss.seekg(0, std::ios::end);
            size = std::max(size, static_cast<uint>(ss.tellg()));
        }
    }

    for (uint r = 0; r < R; r++) {
        if (r == 0)
            os << (R == 1 ? "[ " : "┌ ");
        else if (r < R - 1)
            os << "│ ";
        else
            os << "└ ";
        for(uint c = 0; c < C ; ++c) {
            std::stringstream ss;
            ss << m(r, c) << " ";
            ss.seekg(0, std::ios::end);
            uint csize = ss.tellg();
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