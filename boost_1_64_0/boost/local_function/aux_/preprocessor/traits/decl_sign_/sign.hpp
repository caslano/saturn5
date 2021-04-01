
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
nukB1NWqJJnV9MUBfl5WXsYyTLDnjT8UXkekTfxAuVRMnNz340ihZuJPWjfyiG++hoSCwhBiyrLY9NJrRoKJgfK+c7D7sj2xkes1XhlyHMN/ZIiSeUncHXFIvFjg3c1EmfspFrAqNmXF1XpxG12c1/0L7+BSEo01imuiTR+ZwnnJgg7ECKKHVhrvxTQMC31qCv19gsojvmWNXMz/1EBG1auebdTt+f0rKFc1WA5WERuAWPNJNIa3ZaxZUzAxDCkaCq4aEtVTrl8ZyPblm1LyyknE9IM4liRTAITU2boFvvECVLlROzGrUlGKYXEAp/1zYCipXfr9+dck4wSUgquhITky0PFMFDAFAWkJ2WGdw7LBZZaUKK6aLyN6JHm2EaV36HVCd0ODCS+DyBctVtPnUzIpD3yOjSM+GPgg1AFiD/0i8DXJw0CJUNKLL10OYOJoHtsmivqukGf7wY2ROrVUD3nDi39GPciuvHIbG+7ngCR+54RmrAeklfsV8Aq5WpFJeevnV/8JfXhyS727dZchcsY89ap3Ss2rTOpK0SLUIMrX9FLRrKDWGT+X/A==
*/