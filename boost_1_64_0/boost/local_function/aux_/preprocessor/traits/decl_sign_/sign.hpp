
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
zg2b29TzlfOE/BZKOo7jfhWYrb2fMi7vU9kIgD9navsqbLpfifs07mm6fgqb7kwjpFvj8PxCXXndb448j+nv/rqHjbjuYaOyPihsQRhsUZ5fkGeEIc8M88lvMSJvtus9eeOOdtMDEffO/kg31+rrYOtB+rrd37KejhFx8nT+R3p2nyIxnf+1utWztP636cIH4pmqXO9/qSuuIz5nzMkU5QDp+L1L/8jPlI5lIv0P+8LLBHbYnymRX76fbparf8ZYwzLqwwxkQMrR5rcoZSR6/7Buc1lNqHwOzez0ekBc+/Uww2kOAXSt9fbDfrC7j/t6i7zo6y3PqdraDOOw4VgHlsDWVrut4nbmztZWTf7Tuph/Na/LWCADGWkAZF427iv2vM70V2Dij6u8tivl0kc89yNqmbZcoGtve8rrZtYGtNdJu8YHvbvoA7MMkT+EifyxnrOdYT7U/s6F/DbADUz8ekgFzp+9r8VXogMb9qBfm89OSvuys9A9y9gCNvTE/ga49nrC+SmQVIgXsgFkQ8hGEA8E90OkZd4P2Ueu9EkNE2mmRbze1TYzoa/D80SYLUp/hHzvd3cvXANsjXPio0bPW46Wj6rnSzvxeKNfV+dSwZe++tP7Bo99fK8PBkzap+DUxLsGR89DjnZdoGh5y/uK9J98dcpXN9X0W/nXec3j3tnk7tXOfOOtNgqGt3xSOPiS0ptT5qYu82T8eMMDznxjPf/Zmdet5zM78bqj51Hr+fPRr2vkwIsW6z+PhWBD329o7V7QHUX//nI+J//F319D/uDvJI9oaMXvKrkOM8d9OLaFtCz85UZQwwBIP7Q+LSiRXH+Y4yM8x3Lb+sNF5MMGgB8H4wNXkt/6BXmxq7jP9DiWgTxo0juX6Z3HdXIXAYdyfdLNgZeSV3uZug4s+6q3YHrq+qdzmd5pwGTgPKAXeAawL3m1Q4Bnkrd7NnBT4Fk8H/Yl/3ssz7OJxn97xIf8Nx44BJgLXA1cCPEz3kTmzwdZYPJkPaH8DQL2BA4GZgC3BfYBDgVmA4cBhwGHA4cDc4BbUW9r4KbA7Xl8NI+P5fE9gFsB9wFuDZzA8NXAKtm/izwzfymQYuZvDuvFXGAqcB6wF/f7cT8beDpwU+7ncH9P4HzgPsAzWZ/8sm8SfbE8Xyqkguc7kf44if44mf44h/6YAxwo1q5meQG35PERwDOB2wEXAHdguFyPl+fN19STi3jeS4ADgJfRv4vo16uAI4FX0K9XAicCm4EH8Phq4GzZJ4Vz8zxeSA3PkwK9IG5E+3oB04BpwG2AvYGjgOnAQ4GZwDJgX+CJwCzgSQw/g+FnM5zlyT4Z9PNoyrOG5z+K52/g+QNAsU4zcAzwGOAU4LHAQoaXM7yK4Vznmf0dKHueT13n+XvywNeQL/87+e1/AI8D/gk8AWggvVMBccDTgPFA8szZ9wBbmb7KM0+kPUnADYE9gJnAZCV/6EdwzN87zN+7zN8nzN8K5u9T5u9z4KlAtGkif18CmT+82zvnbxXTR9sp8vcNMBP4rRK/jfG30MRvZfzX2Q6+wXbpTXV9eL4LVWna06fY/j0D7ANcChwFfA5YxvXJjwAuU9fBZ3p9mJ7azu1Lf+/H63J/oLkuXyvjbcx46rp8OzPerkDzPO3UH6g5zx7UH8/rcW9ZnnwOBt6gKc9JjHcQcAPgYcDzgCXAy4ClwMuBhwOvAVYArwdWqvVtX+fyPILpV7G+VbO+HQnsn2hEnM8wJYC1fSGLIPdAWiFDoXNPo36uw5STrfMdarDfZJ3zIG7WmRBz7sMup+jnP5Se4jwH4nQcuxayDDJux0Q5H+LhzxKM3xHmPTU0NyIbqJ8fAcQxc47E7FM=
*/