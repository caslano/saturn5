
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