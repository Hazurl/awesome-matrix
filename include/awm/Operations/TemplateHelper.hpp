#pragma once



namespace awm {

template<typename T, unsigned int R, unsigned int C>
class Matrix;

namespace details {

    template<typename M>
    struct GetRow                               {};
    template<typename T, unsigned int R, unsigned int C>
    struct GetRow<Matrix<T, R, C>>              { static constexpr unsigned int value = R; };

    template<typename M>
    struct GetColumn                            {};
    template<typename T, unsigned int R, unsigned int C>
    struct GetColumn<Matrix<T, R, C>>           { static constexpr unsigned int value = C; };

    template<typename M>
    struct GetUnderlyingType                    {};
    template<typename T, unsigned int R, unsigned int C>
    struct GetUnderlyingType<Matrix<T, R, C>>   { using Type = T; };

    template<typename Op>
    struct AllowedExtractor                     { static constexpr bool value = false; };

    template<template<template<typename, unsigned int, unsigned int>, typename, unsigned int, unsigned int, bool> typename Op, template<typename, unsigned int, unsigned int> typename M, typename T, unsigned int R, unsigned int C, bool b>
    struct AllowedExtractor<Op<M, T, R, C, b>>  { static constexpr bool value = b; };

    template<typename M, template<template<typename, unsigned int, unsigned int>, typename, unsigned int, unsigned int, bool> typename Op>
    struct OpAllowed                            { static constexpr bool value = AllowedExtractor<
                                                    Op <
                                                        Matrix,
                                                        GetUnderlyingType<M>,
                                                        GetRow<M>,
                                                        GetColumn<M>
                                                    >>::value; };

}

template<typename M>
constexpr unsigned int get_row_v = details::GetRow<M>::value;

template<typename M>
constexpr unsigned int get_column_v = details::GetColumn<M>::value;

template<typename M>
using get_uderlying_type_t = typename details::GetUnderlyingType<M>::value;

template<typename M, template<template<typename, unsigned int, unsigned int>, typename, unsigned int, unsigned int, bool> typename Op>
constexpr bool is_op_allowed = details::OpAllowed<M, Op>::value;

}