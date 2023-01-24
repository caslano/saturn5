
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
0cPYWMe4qqNY9AfuFAh3cTEuISsjT03K/F3ILgUKwzNjh4maDrRpdrYvnSOeDyXkH/pnbyRkx7bS2fRU2/6ja5y0ORvs9p37kSk4aHKsqwWruaGmDDpqALuJDzgO6uSRYl1tAfFkrawVWB1Pc3MP8MyXWcmpSy5HluPsZ86m/yi7vIycPeD8MSR+5S2O0hyWXKn0hXSeXMBtd0tSO5X8b9AKvrl99JxfiYUOVC5aavhaapx+ruiqt2l/pfB1SRgKup/QiH1LzXlmlPi6Hjn0dhrUuIf6IiPkc2kr1FZ83baHaJsto52laoJiV5qKR1BEQ01LTf/rA2X+km/JT33LmZetl5en5RVbXZe/CTOFw76mhm3ldMoHOFMJttU457K+jVdozxXyx3yPlEiH3r1G2n4qJduTvCm2WI2h05Emwh63uJC7OpW5vFossp6lox9vIMvGHFVV/aGmXFZBQW7KKlmGw9AcXs1V5bG2FjqhqJ1K8kqWntmvZoo7Kl/yc2tFXgNFXosl9DjMrWuv8fI1kw9KiBcrPac1jfPROgcU1USE8mQnC4AbIq1lTi0tVWJrbKYJ/NShzFGq8orGpaXDS+SliIgfjo6mh6EVqWwrbaC/mS7e6ObYL7Ox7GBf1a9AHcBipYCRIv+oncMHSswJ3g7P2B+tUYteJ9z1zzlYbmUFrrUlJd11BZOz86Y28F41cmUjjBWKbEzj9Kys
*/