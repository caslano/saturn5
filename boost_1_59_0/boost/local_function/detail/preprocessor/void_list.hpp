
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_HPP_

#include <boost/local_function/detail/preprocessor/keyword/void.hpp>
#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/to_tuple.hpp>

// PRIVATE //

// Argument: (token1)...
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_FROM_SEQ_(unused, seq) \
    BOOST_PP_TUPLE_TO_LIST(BOOST_PP_SEQ_SIZE(seq), BOOST_PP_SEQ_TO_TUPLE(seq))

// Token: void | token1
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_HANDLE_VOID_( \
        is_void_macro, token) \
    BOOST_PP_IIF(is_void_macro(token), \
        BOOST_PP_NIL \
    , \
        (token, BOOST_PP_NIL) \
    )

// Token: (a)(b)... | empty | void | token
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_HANDLE_SEQ_( \
        is_void_macro, token) \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(token), /* unary paren (a)... */ \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_FROM_SEQ_ \
    , \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_HANDLE_VOID_ \
    )(is_void_macro, token)

#ifdef BOOST_NO_CXX11_VARIADIC_MACROS

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_(is_void_macro, seq) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_HANDLE_SEQ_(is_void_macro, seq)

#else // VARIADICS

// FUTURE: Replace this with BOOST_PP_VARIADIC_SIZE when and if
// BOOST_PP_VARIAIDCS detection will match !BOOST_NO_CXX11_VARIADIC_MACROS (for now
// Boost.Preprocessor and Boost.Config disagree on detecting compiler variadic
// support while this VARIADIC_SIZE works on compilers not detected by PP).
#if BOOST_MSVC
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_VARIADIC_SIZE_(...) \
        BOOST_PP_CAT(BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_VARIADIC_SIZE_I_(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,),)
#else // MSVC
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_VARIADIC_SIZE_(...) \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_VARIADIC_SIZE_I_(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,)
#endif // MSVC
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_VARIADIC_SIZE_I_(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, size, ...) size

// Argument: token1, ...
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_FROM_VARIADIC_(unused, ...) \
    BOOST_PP_TUPLE_TO_LIST( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_VARIADIC_SIZE_( \
                    __VA_ARGS__), (__VA_ARGS__))

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_(is_void_macro, ...) \
    BOOST_PP_IIF(BOOST_PP_EQUAL( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_VARIADIC_SIZE_( \
                    __VA_ARGS__), 1), \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_HANDLE_SEQ_ \
    , \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_FROM_VARIADIC_ \
    )(is_void_macro, __VA_ARGS__)

#endif // VARIADICS

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_NEVER_(tokens) \
    0 /* void check always returns false */

// PUBLIC //

// NOTE: Empty list must always be represented is void (which is also a way to
// specify no function parameter) and it can never be empty because (1)
// IS_EMPTY(&var) fails (because of the leading non alphanumeric symbol) and
// (2) some compilers (MSVC) fail to correctly pass empty macro parameters
// even if they support variadic macros. Therefore, always using void to
// represent is more portable.

#ifdef BOOST_NO_CXX11_VARIADIC_MACROS

// Expand `void | (a)(b)...` to pp-list `NIL | (a, (b, NIL))`.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST(sign) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_VOID_BACK, sign)

// Expand `(a)(b)...` to pp-list `(a, (b, NIL))`.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_NON_VOID_LIST(seq) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_NEVER_, seq)

#else // VARIADICS

// Expand `void | (a)(b)... | a, b, ...` to pp-list `NIL | (a, (b, NIL))`.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST(...) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_VOID_BACK, __VA_ARGS__)

// Expand `(a)(b)... | a, b, ...` to pp-list `(a, (b, NIL))`.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_NON_VOID_LIST(...) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST_NEVER_, __VA_ARGS__)

#endif // VARIADICS

#endif // #include guard


/* void_list.hpp
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
*/