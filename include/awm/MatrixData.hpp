#pragma once

#include <array>

namespace awm {

#define ACCESSOR(name, index) \
                    T& name()       { return this->values[index]; } \
    constexpr const T& name() const { return this->values[index]; }

template<typename T, unsigned int R, unsigned int C>
class MatrixData {
public:
    std::array<T, R*C> values;
};

template<typename T, unsigned int R, unsigned int C> 
class MatrixAccessor : public MatrixData<T, R, C> {};

template<typename T> 
class MatrixAccessor<T, 1, 1> : public MatrixData<T, 1, 1> {
public:
    ACCESSOR(x, 0)
    ACCESSOR(m00, 0)
};

template<typename T> 
class MatrixAccessor<T, 1, 2> : public MatrixData<T, 1, 2> {
public:

    ACCESSOR(x, 0)
    ACCESSOR(y, 1)

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)

};

template<typename T> 
class MatrixAccessor<T, 1, 3> : public MatrixData<T, 1, 3> {
public:

    ACCESSOR(x, 0)
    ACCESSOR(y, 1)
    ACCESSOR(z, 2)

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)
    ACCESSOR(m02, 2)

};

template<typename T> 
class MatrixAccessor<T, 1, 4> : public MatrixData<T, 1, 4> {
public:

    ACCESSOR(x, 0)
    ACCESSOR(y, 1)
    ACCESSOR(z, 2)
    ACCESSOR(w, 3)

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)
    ACCESSOR(m02, 2)
    ACCESSOR(m03, 3)

};

template<typename T> 
class MatrixAccessor<T, 2, 1> : public MatrixData<T, 2, 1> {
public:

    ACCESSOR(x, 0)
    ACCESSOR(y, 1)

    ACCESSOR(m00, 0)
    ACCESSOR(m10, 1)

};

template<typename T> 
class MatrixAccessor<T, 2, 2> : public MatrixData<T, 2, 2> {
public:

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)

    ACCESSOR(m10, 2)
    ACCESSOR(m11, 3)

};

template<typename T> 
class MatrixAccessor<T, 2, 3> : public MatrixData<T, 2, 3> {
public:

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)
    ACCESSOR(m02, 2)

    ACCESSOR(m10, 3)
    ACCESSOR(m11, 4)
    ACCESSOR(m12, 5)

};

template<typename T> 
class MatrixAccessor<T, 2, 4> : public MatrixData<T, 2, 4> {
public:

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)
    ACCESSOR(m02, 2)
    ACCESSOR(m03, 3)

    ACCESSOR(m10, 4)
    ACCESSOR(m11, 5)
    ACCESSOR(m12, 6)
    ACCESSOR(m13, 7)

};

template<typename T> 
class MatrixAccessor<T, 3, 1> : public MatrixData<T, 3, 1> {
public:

    ACCESSOR(x, 0)
    ACCESSOR(y, 1)
    ACCESSOR(z, 2)

    ACCESSOR(m00, 0)

    ACCESSOR(m10, 1)

    ACCESSOR(m20, 2)

};

template<typename T> 
class MatrixAccessor<T, 3, 2> : public MatrixData<T, 3, 2> {
public:

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)
    ACCESSOR(m02, 2)

    ACCESSOR(m10, 3)
    ACCESSOR(m11, 4)
    ACCESSOR(m12, 5)

};

template<typename T> 
class MatrixAccessor<T, 3, 3> : public MatrixData<T, 3, 3> {
public:

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)
    ACCESSOR(m02, 2)

    ACCESSOR(m10, 3)
    ACCESSOR(m11, 4)
    ACCESSOR(m12, 5)

    ACCESSOR(m20, 6)
    ACCESSOR(m21, 7)
    ACCESSOR(m22, 8)

};

template<typename T> 
class MatrixAccessor<T, 3, 4> : public MatrixData<T, 3, 4> {
public:

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)
    ACCESSOR(m02, 2)
    ACCESSOR(m03, 3)

    ACCESSOR(m10, 4)
    ACCESSOR(m11, 5)
    ACCESSOR(m12, 6)
    ACCESSOR(m13, 7)

    ACCESSOR(m20, 8)
    ACCESSOR(m21, 9)
    ACCESSOR(m22, 10)
    ACCESSOR(m23, 11)

};

template<typename T> 
class MatrixAccessor<T, 4, 1> : public MatrixData<T, 4, 1> {
public:

    ACCESSOR(x, 0)
    ACCESSOR(y, 1)
    ACCESSOR(z, 2)
    ACCESSOR(w, 3)

    ACCESSOR(m00, 0)

    ACCESSOR(m10, 1)

    ACCESSOR(m20, 2)

    ACCESSOR(m30, 3)

};

template<typename T> 
class MatrixAccessor<T, 4, 2> : public MatrixData<T, 4, 2> {
public:

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)

    ACCESSOR(m10, 2)
    ACCESSOR(m11, 3)

    ACCESSOR(m20, 4)
    ACCESSOR(m21, 5)

    ACCESSOR(m30, 6)
    ACCESSOR(m31, 7)

};

template<typename T> 
class MatrixAccessor<T, 4, 3> : public MatrixData<T, 4, 3> {
public:

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)
    ACCESSOR(m02, 2)

    ACCESSOR(m10, 3)
    ACCESSOR(m11, 4)
    ACCESSOR(m12, 5)

    ACCESSOR(m20, 6)
    ACCESSOR(m21, 7)
    ACCESSOR(m22, 8)

    ACCESSOR(m30, 9)
    ACCESSOR(m31, 10)
    ACCESSOR(m32, 11)

};

template<typename T> 
class MatrixAccessor<T, 4, 4> : public MatrixData<T, 4, 4> {
public:

    ACCESSOR(m00, 0)
    ACCESSOR(m01, 1)
    ACCESSOR(m02, 2)
    ACCESSOR(m03, 3)

    ACCESSOR(m10, 4)
    ACCESSOR(m11, 5)
    ACCESSOR(m12, 6)
    ACCESSOR(m13, 7)

    ACCESSOR(m20, 8)
    ACCESSOR(m21, 9)
    ACCESSOR(m22, 10)
    ACCESSOR(m23, 11)

    ACCESSOR(m30, 12)
    ACCESSOR(m31, 13)
    ACCESSOR(m32, 14)
    ACCESSOR(m33, 15)

};

#undef ACCESSOR

}