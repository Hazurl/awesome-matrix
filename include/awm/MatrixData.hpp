#pragma once

namespace awm {

#define POINTER_DATA(size)\
    inline T*       pointer_data ()       { return data; }\
    inline const T* pointer_data () const { return data; }\
    inline T*       pointer_data_end ()       { return data + size; }\
    inline const T* pointer_data_end () const { return data + size; }

#define POINTER_DATA_NULLPTR()\
    inline T*       pointer_data ()       { return nullptr; }\
    inline const T* pointer_data () const { return nullptr; }\
    inline T*       pointer_data_end ()       { return nullptr; }\
    inline const T* pointer_data_end () const { return nullptr; }

template<typename T, unsigned int R, unsigned int C> 
class MatrixData {
public:
    T data[R*C];
protected:
    POINTER_DATA(R*C)
};

template<typename T, unsigned int C> 
class MatrixData<T, 0, C> {
protected:
    POINTER_DATA_NULLPTR()
};

template<typename T, unsigned int R> 
class MatrixData<T, R, 0> {
protected:
    POINTER_DATA_NULLPTR()
};

template<typename T> 
class MatrixData<T, 0, 0> {
protected:
    POINTER_DATA_NULLPTR()
};

template<typename T> 
class MatrixData<T, 1, 1> {
public:

    union {
        T data[1];
        T x;
        T m00;
    };

    explicit operator T& () & {
        return data[0];
    }

    explicit operator const T& () const& {
        return data[0];
    }

    explicit operator T&& () && {
        return std::move(data[0]);
    }

protected:
    POINTER_DATA(1)

};

template<typename T> 
class MatrixData<T, 1, 2> {
public:

    union {
        T data[2];
        struct {
            T x, y;
        };
        struct {
            T m00, m01;
        };
    };

protected:
    POINTER_DATA(2)

};

template<typename T> 
class MatrixData<T, 1, 3> {
public:

    union {
        T data[3];
        struct {
            T x, y, z;
        };
        struct {
            T m00, m01, m02;
        };
    };

protected:
    POINTER_DATA(3)

};

template<typename T> 
class MatrixData<T, 1, 4> {
public:

    union {
        T data[4];
        struct {
            T x, y, z, w;
        };
        struct {
            T m00, m01, m02, m03;
        };
    };

protected:
    POINTER_DATA(4)

};

template<typename T> 
class MatrixData<T, 2, 1> {
public:

    union {
        T data[2];
        struct {
            T x, y;
        };
        struct {
            T m00, 
              m01;
        };
    };

protected:
    POINTER_DATA(2)

};

template<typename T> 
class MatrixData<T, 2, 2> {
public:

    union {
        T data[4];
        struct {
            T m00, m01, 
              m10, m11;
        };
    };

protected:
    POINTER_DATA(4)

};

template<typename T> 
class MatrixData<T, 2, 3> {
public:

    union {
        T data[6];
        struct {
            T m00, m01, m02,
              m10, m11, m12;
        };
    };

protected:
    POINTER_DATA(6)

};

template<typename T> 
class MatrixData<T, 2, 4> {
public:

    union {
        T data[6];
        struct {
            T m00, m01, m02, m03,
              m10, m11, m12, m13;
        };
    };

protected:
    POINTER_DATA(8)

};

template<typename T> 
class MatrixData<T, 3, 1> {
public:

    union {
        T data[3];
        struct {
            T x, y, z;
        };
        struct {
            T m00, 
              m01, 
              m02;
        };
    };

protected:
    POINTER_DATA(3)

};

template<typename T> 
class MatrixData<T, 3, 2> {
public:

    union {
        T data[6];
        struct {
            T m00, m01,
              m10, m11,
              m20, m21;
        };
    };

protected:
    POINTER_DATA(6)

};

template<typename T> 
class MatrixData<T, 3, 3> {
public:

    union {
        T data[9];
        struct {
            T m00, m01, m02,
              m10, m11, m12,
              m20, m21, m22;
        };
    };

protected:
    POINTER_DATA(9)

};

template<typename T> 
class MatrixData<T, 3, 4> {
public:

    union {
        T data[3];
        struct {
            T m00, m01, m02, m03,
              m10, m11, m12, m13,
              m20, m21, m22, m23;
        };
    };

protected:
    POINTER_DATA(12)

};

template<typename T> 
class MatrixData<T, 4, 1> {
public:

    union {
        T data[4];
        struct {
            T x, y, z, w;
        };
        struct {
            T m00, m01, m02, m03;
        };
    };

protected:
    POINTER_DATA(4)

};

template<typename T> 
class MatrixData<T, 4, 2> {
public:

    union {
        T data[8];
        struct {
            T m00, m01,
              m10, m11,
              m20, m21,
              m30, m31;
        };
    };

protected:
    POINTER_DATA(8)

};

template<typename T> 
class MatrixData<T, 4, 3> {
public:

    union {
        T data[12];
        struct {
            T m00, m01, m02,
              m10, m11, m12,
              m20, m21, m22,
              m30, m31, m32;
        };
    };

protected:
    POINTER_DATA(12)

};

template<typename T> 
class MatrixData<T, 4, 4> {
public:

    union {
        T data[16];
        struct {
            T m00, m01, m02, m03,
              m10, m11, m12, m13,
              m20, m21, m22, m23,
              m30, m31, m32, m33;
        };
    };

protected:
    POINTER_DATA(16)

};

}