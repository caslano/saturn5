
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