
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
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
*/