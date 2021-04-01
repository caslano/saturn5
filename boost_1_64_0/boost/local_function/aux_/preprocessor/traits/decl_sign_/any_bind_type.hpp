
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_TYPE_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_TYPE_HPP_

#include <boost/local_function/detail/preprocessor/keyword/const_bind.hpp>
#include <boost/local_function/detail/preprocessor/keyword/this.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE_(sign) \
    /* using PP_EXPAND here does not work on MSVC */ \
    BOOST_PP_TUPLE_REM(1) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT(sign) \
    BOOST_PP_EMPTY /* always trail EMPTY because bind type is optional */

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE_( \
        sign) \
    /* using PP_EXPAND here does not work on MSVC */ \
    BOOST_PP_TUPLE_EAT(1) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT(sign)

#define this_BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_REMOVE_THIS_ \
    /* must expand to nothing */

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE_(sign) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE( \
        /* can't use `THISUNDERSCIRE_REMOVE_BACK` because `sign` contains */ \
        /* multiple tokens (and not just one token) so */ \
        /* `IS_THISUNDERSCORE_BACK` does not work (but we know `sign` ends */ \
        /* with this_ if we here so we can manually force the removal using */ \
        BOOST_PP_CAT(sign, \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_REMOVE_THIS_) \
    ) \
    /* do not append PP_EMPTY because ANY_BIND_WITH_TYPE macro above */ \
    /* already appends it */

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE(sign) \
    BOOST_PP_IS_UNARY( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT( \
                    sign))

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE(sign) \
    BOOST_PP_IIF( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE( \
                    sign),\
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE_ \
    , \
        BOOST_PP_EMPTY \
        BOOST_PP_TUPLE_EAT(1) \
    )(sign)

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE( \
        sign) \
    BOOST_PP_IIF( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE( \
                    sign),\
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE_ \
    , \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT \
    )(sign)

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE(sign) \
    BOOST_PP_IIF( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE( \
                    sign),\
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE_ \
    , \
        BOOST_PP_EMPTY \
        BOOST_PP_TUPLE_EAT(1) \
    )(sign)

#endif // #include guard


/* any_bind_type.hpp
aVLf4UZhOoeRqVUA02jg5TDV+hAOJS0fE0w1VdJn2xuY5m1P32CkMXUaxkFdfq6kujwMMVa2LkF5bPc3iAV+u4MC5SK9o5G8NFnapMekx+G3HWkfBOc4k0eFHTJgGxCGkmVt5D+UpBRYc+3OFn3dYhHB4hvE5JYL2we4Gw3k6USTF7xpe9JJEd46ITIkQDfO/BZ7K0LWD2Zsk2Es3fBhpoqrAqriK8sUS5AXmYMC/uRLlBFfHk21ddj9wnuxhIkH0u5VGT57Gh3NJKs7Wmt5P4MCMyyFGLuEaywNCcKjiQYbk94qz70JT7cez4b3cJGX80z+rZtSRvHcGfZizaY5NlKpwMIVjUEMmKZEJU8fQjqhAK6FKkYk6550acRy9trgZlBgarmSTe8/5g6xfYKJsLPDLObqPrC9gKPCq9eNV3Q/wmKyHZrCqpf8xeKgjATnmzI0TKOdbnSqM8ZZF6D3x8U+IQhb4A4ks75c6KYrYFe2N44XilusOaxoOWxLc2aFuFnbHznfdZV6clBAaQ64Osu/OufyCadRbVnQVv+hRDxQ6zgdpVlLLUL0Aw==
*/