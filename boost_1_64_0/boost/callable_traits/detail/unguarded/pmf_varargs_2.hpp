/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

*/

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    false, // IsTransactionSafe
    false, // IsNoexcept
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS;
};

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    false,
    true,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;
};

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    true,
    false,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER;
};

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    true,
    true,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
            BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;
};

#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::false_type
#include <boost/callable_traits/detail/unguarded/pmf_varargs_3.hpp>

#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

#ifdef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE

#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::true_type
#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE transaction_safe
#include <boost/callable_traits/detail/unguarded/pmf_varargs_3.hpp>
#endif

#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

/* pmf_varargs_2.hpp
/D5doI1GYd4R0DXmItjGD3BR7zsFPwER1TY6T/roZ71+Fh6y7t8ohVaTnqF8FJ/1akLySwCNwF+01oo7qc4yEp+/LWuJScsNGZ9/L/F5IVb+da6iaGy4pshUA6Npy1pirxIGUqcx49uDb8wrUoj0OSorzZ0tbR7b6cOtOSltGty2fxaWZD6R41GPiKxkUIAjLxi4MFBuYEUUzKHWhfpJAvkDomyFqnTf/oAl9kHcKr1hjtvp7Fe5d0iGSMLfsEdYdvZfnwhCmQtIt32b0qfvuAUT7ENmhiyy0hSIhjrfEoUndn+80oBP33Yp4Oj67JNktxMeauj2ZKtk43sARD8hmn6rr0n/AsWT4YTCNKCZmcYbR4S14aWba4bxSpahmhgzoxe8i6GpwmZf8B5IYoC0Mx9M/D/wToT/GwktNZGfqT0f54tjrH5+uxOhqPKzbHKcAmsBdfLXDsC+otn2BQra/TMR8NnYXYDvmI8A10qCfP37ic4fmySKyxWYj9qIbCsT/b0HG2eyvlKTEF0Rv0ep3F7XQUO1nrwFyOZVFjv8kidF6Snw9fsQVPYHNw==
*/