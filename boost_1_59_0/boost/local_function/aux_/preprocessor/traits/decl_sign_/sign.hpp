
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_sign_/validate.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_sign_/any_bind_type.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/nil.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/set_error.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/validate.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/append.hpp>
#include <boost/local_function/detail/preprocessor/keyword/const_bind.hpp>
#include <boost/local_function/detail/preprocessor/keyword/bind.hpp>
#include <boost/local_function/detail/preprocessor/keyword/return.hpp>
#include <boost/local_function/detail/preprocessor/keyword/default.hpp>
#include <boost/local_function/detail/preprocessor/keyword/thisunderscore.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/list/fold_left.hpp>

// PRIVATE //

// Parse const binds.

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_THIS_( \
        decl_traits, sign) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_CONST_BIND_THIS_TYPE( \
            decl_traits, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE( \
                    sign))

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_VAR_( \
        decl_traits, sign) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_CONST_BIND(decl_traits, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE(\
                    sign), \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE( \
                    sign))

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_( \
        decl_traits, sign) \
    /* check from back because non `this` bounds might have `&` in front */ \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THISUNDERSCORE_BACK(\
            /* remove all leading symbols `[const] bind [(type)] ...` */ \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE(\
                    sign)),\
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_THIS_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_VAR_ \
    )(decl_traits, sign)

// Parse binds.

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_THIS_( \
        decl_traits, sign) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_BIND_THIS_TYPE(decl_traits, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE( \
            sign))

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_VAR_( \
        decl_traits, sign) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_BIND(decl_traits, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE(\
                    sign), \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE( \
                    sign))

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_( \
        decl_traits, sign) \
    /* check from back because non `this` bounds might have `&` in front */ \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THISUNDERSCORE_BACK(\
            /* remove all leading symbols `[const] bind [(type)] ...` */ \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE(\
                    sign)), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_THIS_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_VAR_ \
    )(decl_traits, sign)

// Parse all elements.

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_( \
        s, decl_traits, sign) \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_RETURN_FRONT(sign), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_RETURN \
    , BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_BIND_FRONT(sign), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_ \
    , BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT( \
            sign), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_ \
    , BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT( \
            sign), \
        /* elem is `default ...` where leading default is kept because */ \
        /* default value might not be alphanumeric (so it fails later CAT */ \
        /* for checks), leading default will be removed later when getting */ \
        /* the default value */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_PARAM_DEFAULT \
    , /* else, it is a function parameter */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_PARAM \
    ))))(decl_traits, sign)

// Parse params after following precondition has been validated by caller.
// Precondition: If list contains a default param value `..., default, ...`,
// the default value element is never 1st (it always has a previous elem) and
// its previous element is a unbind param (no const-bind and no bind).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID(sign) \
    BOOST_PP_LIST_FOLD_LEFT( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL, sign)

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_OK_(sign, unused) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALID(sign))

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ERR_(unused, error) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL, error)

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_(sign, defaults_error) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(defaults_error (/* expand EMPTY */)), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_OK_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ERR_ \
    )(sign, defaults_error)

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN(sign) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_(sign, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE(sign))

#endif // #include guard


/* sign.hpp
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
*/