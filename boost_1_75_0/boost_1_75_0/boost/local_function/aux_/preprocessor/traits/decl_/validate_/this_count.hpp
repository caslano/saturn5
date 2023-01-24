
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/set_error.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_const_binds.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_binds.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/list/size.hpp>

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT( \
        decl_traits) \
    BOOST_PP_IIF(BOOST_PP_GREATER(BOOST_PP_LIST_SIZE(BOOST_PP_LIST_APPEND( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                    decl_traits), \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES( \
                    decl_traits))), \
            1), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR \
    , /* do nothing (keeping previous error, if any) */ \
        decl_traits BOOST_PP_TUPLE_EAT(2) \
    )(decl_traits, /* trailing `EMPTY` because error might not be present */ \
            ERROR_cannot_bind_object_this_multiple_times BOOST_PP_EMPTY)

#endif // #include guard


/* this_count.hpp
/7vAWxxPM54XOYz2ShTjfQw+nuz+Tudsougwxzjp8/ExzD0CXHy1tZVTmRIVF1czNLT3EfeytLS2tPzm4+OnpGSoqpqisbI2nZAbl4aL/cEeRfwvf5GVl9eSMJHU4P7u2ailXvQXjYFRRhOOXRWV4vALxiIqlyF07QW4VwZ3yuT3xhFixTMmBuD1peASlSGjJFDwYXtsiALzxVFERJK7u293ZHx64p0PQ7U6uwYNSrkPKiC1ReoJ4xfjjdaWhobvGBgWuh9o1Vi73W6szLIElYr4KyJiRTzqiwt/E0sdXi3KOtwc0C/Kq8RvnNZiPDmVVMnFvgKLYiop+UflHG7FX2izq0sqK9csgLyH+kQ1LAtWY4YUFPrVcz2Ozr56co5TyZub2D5a1rovu/FRP/Hw+BjVTe3sTBUV3b4aSdnY2KqolGmZqjKO4jnuOl6heNh4yH/h9ZaUh6Tr6i+35b1agLtPA1au1m5u4p6eZiCZRK0fZeqpDHgsUsbajirmHh5KCgpKurp+Xl5+mpqSGhp+SpO7UQTdD3uZ4KbbjK0EyHcPW8syDj4azQIOqy8hVq7IaR1a6mWq6mVJDphdT0zaqRh/A0/hF+EuFjqkjjVCMrjt27adwuWdwrOrq67l5YDrcXGy7L61NYMTzRodBkU5eC97awsLe6tqnnSnxmX55F9VrRxqBeMa1k5zVgVauoWq8a3+WurVGrsju8uJ
*/