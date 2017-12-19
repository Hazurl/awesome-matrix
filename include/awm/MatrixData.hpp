#pragma once

#include <awm/config.hpp>

namespace awm {

template<typename T, uint R, uint C> 
class MatrixData {
public:

    T data[R*C];

protected:
    inline T*       pointer_data ()       { return data; }
    inline const T* pointer_data () const { return data; }

    inline T*       pointer_data_end ()       { return data + R*C; }
    inline const T* pointer_data_end () const { return data + R*C; }

};

template<typename T, uint C> 
class MatrixData<T, 0, C> {
public:

protected:
    inline T*       pointer_data ()       { return nullptr; }
    inline const T* pointer_data () const { return nullptr; }

    inline T*       pointer_data_end ()       { return nullptr; }
    inline const T* pointer_data_end () const { return nullptr; }

};

template<typename T, uint R> 
class MatrixData<T, R, 0> {
public:

protected:
    inline T*       pointer_data ()       { return nullptr; }
    inline const T* pointer_data () const { return nullptr; }

    inline T*       pointer_data_end ()       { return nullptr; }
    inline const T* pointer_data_end () const { return nullptr; }

};

template<typename T> 
class MatrixData<T, 0, 0> {
public:

protected:
    inline T*       pointer_data ()       { return nullptr; }
    inline const T* pointer_data () const { return nullptr; }

    inline T*       pointer_data_end ()       { return nullptr; }
    inline const T* pointer_data_end () const { return nullptr; }

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
    inline T*       pointer_data ()       { return data; }
    inline const T* pointer_data () const { return data; }

    inline T*       pointer_data_end ()       { return data + 1; }
    inline const T* pointer_data_end () const { return data + 1; }

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
    inline T*       pointer_data ()       { return data; }
    inline const T* pointer_data () const { return data; }

    inline T*       pointer_data_end ()       { return data + 2; }
    inline const T* pointer_data_end () const { return data + 2; }

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
    inline T*       pointer_data ()       { return data; }
    inline const T* pointer_data () const { return data; }

    inline T*       pointer_data_end ()       { return data + 3; }
    inline const T* pointer_data_end () const { return data + 3; }

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
    inline T*       pointer_data ()       { return data; }
    inline const T* pointer_data () const { return data; }

    inline T*       pointer_data_end ()       { return data + 4; }
    inline const T* pointer_data_end () const { return data + 4; }

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
            T m00, m01;
        };
    };

protected:
    inline T*       pointer_data ()       { return data; }
    inline const T* pointer_data () const { return data; }

    inline T*       pointer_data_end ()       { return data + 2; }
    inline const T* pointer_data_end () const { return data + 2; }

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
            T m00, m01, m02;
        };
    };

protected:
    inline T*       pointer_data ()       { return data; }
    inline const T* pointer_data () const { return data; }

    inline T*       pointer_data_end ()       { return data + 3; }
    inline const T* pointer_data_end () const { return data + 3; }

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
    inline T*       pointer_data ()       { return data; }
    inline const T* pointer_data () const { return data; }

    inline T*       pointer_data_end ()       { return data + 4; }
    inline const T* pointer_data_end () const { return data + 4; }

};

template<typename T> 
class MatrixData<T, 2, 2> {
public:

    union {
        T data[4];
        struct {
            T m00, m01, m10, m11;
        };
    };

protected:
    inline T*       pointer_data ()       { return data; }
    inline const T* pointer_data () const { return data; }

    inline T*       pointer_data_end ()       { return data + 4; }
    inline const T* pointer_data_end () const { return data + 4; }

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
    inline T*       pointer_data ()       { return data; }
    inline const T* pointer_data () const { return data; }

    inline T*       pointer_data_end ()       { return data + 9; }
    inline const T* pointer_data_end () const { return data + 9; }

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
    inline T*       pointer_data ()       { return data; }
    inline const T* pointer_data () const { return data; }

    inline T*       pointer_data_end ()       { return data + 16; }
    inline const T* pointer_data_end () const { return data + 16; }

};

}