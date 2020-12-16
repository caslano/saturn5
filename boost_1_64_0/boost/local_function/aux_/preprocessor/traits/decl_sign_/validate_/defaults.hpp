
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_HPP_

#include <boost/local_function/detail/preprocessor/keyword/const_bind.hpp>
#include <boost/local_function/detail/preprocessor/keyword/bind.hpp>
#include <boost/local_function/detail/preprocessor/keyword/default.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/size.hpp>
#include <boost/preprocessor/list/at.hpp>

// PRIVATE //

#define \
BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_IS_UNBIND_( \
        sign) \
    /* PP_OR/PP_BITOR (instead of IIF) don't expand on MSVC */ \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT(sign),\
        0 \
    , BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT( \
            sign), \
        0 \
    , BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_BIND_FRONT(sign), \
        0 \
    , \
        1 \
    )))

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PREV_( \
        sign, index, error) \
    BOOST_PP_IIF( \
  BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_IS_UNBIND_( \
                    BOOST_PP_LIST_AT(sign, BOOST_PP_DEC(index))), \
        error /* no err, fwd existing one if any */ \
    , \
        BOOST_PP_CAT(BOOST_PP_CAT(ERROR_default_value_at_element_, \
                BOOST_PP_INC(index)), _must_follow_an_unbound_parameter) \
        BOOST_PP_EMPTY /* because error might not be present */ \
    )

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_INDEX_( \
        sign, index, error) \
    BOOST_PP_IF(index, /* can't use IIF because index can be any number */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PREV_ \
    , \
        ERROR_default_value_cannot_be_specified_as_the_first_element \
        BOOST_PP_EMPTY /* because error might not be present */ \
        BOOST_PP_TUPLE_EAT(3) \
    )(sign, index, error)

// While's operation.

#define \
BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_OP_DATA_( \
        sign, index, error) \
    ( \
        sign \
    , \
        BOOST_PP_INC(index) \
    , \
        BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT( \
                BOOST_PP_LIST_AT(sign, index)), \
  BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_INDEX_ \
        , \
            error BOOST_PP_TUPLE_EAT(3) /* no err, fwd existing one if any */\
        )(sign, index, error) \
    )

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_OP_(d, \
        sign_index_error) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_OP_DATA_( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 1, sign_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 2, sign_index_error))

// While predicate.

#define \
BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PRED_DATA_( \
        sign, index, error) \
    BOOST_PP_BITAND( \
          BOOST_PP_IS_EMPTY(error (/* expand empty */) ) \
        , BOOST_PP_LESS(index, BOOST_PP_LIST_SIZE(sign)) \
    )

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PRED_( \
        d, sign_index_error) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PRED_DATA_( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 1, sign_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 2, sign_index_error))

// PUBLIC //

// Validate parameters default values: `default ...` cannot be 1st element and
// it must follow an unbind param. Expand to `EMPTY` if no error, or
// `ERROR_message EMPTY` if error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS(sign) \
    BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_WHILE( \
  BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PRED_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_OP_,\
            (sign, 0, BOOST_PP_EMPTY)))

#endif // #include guard


/* defaults.hpp
wAZCCIGEEO4QQjgEBIRwyhEgQjjkMAk5IDYkSw4aATVcXsUaW7SIXFVUqqixVYtaNVatWq3Go4oWNYpatLREijdqv3n7zeTt7tvsBvD41R3459t58+735s3M/33v/4L2CwPji31KDggOMR5V89lC+3P85sR3rcL+3EHO574BbM95667cB7ovsBE4gPPUqcC3aH/uXeAEzm/P5vz2cs5vF3N+++fAI8C1DL+O8W5lvNuEO+dvLfw+5LdoNXkxvfhN3pV8ikRgG/JbegCTgL2AC8jfSAZO1MMCF5PvcgGv55HPUgLsB6wC9gfeCUwB3gscALyffJY/AYcAHwcOBT4FHAZ8Fjgc+HfgCOBrnI9+HTgKeAg4FvgRcBzngScBwZkR88/jgOcCzwNmAp8GzgY+B1wA/BtwDvBl4FzgEWA28HPgPODX9Ed+CL/x8J3Fc5kfcgXn+38BTKS9v7PJRxoN3AY8B1gLnEq+1HnkS83jvs4LuY9zEfdxLmY4k5/SQvo3Mv1dTH8309/D9O9g+jcz/b1M/xamfyvT/x3Tv53p38H0a8zvLdQJ028LqWT6d0v75bfhfvk9pP3y68nPug84GHg/+/cfmb8HgGOBfwJOAz4CnAN8FDif4Y18NLWQj8eZjyeZj78wH08xH68wH88wH39lPp5lPv7GfDQwHy8xHy8zH6+Y7cFvGqDTsz3IG9HIF2kLbCJP7WPuy/8lsD95NsPIs5nEfdyXAD8FXsB93Eu4j3sZwxl8iiamP1mxT/si8h2WAHX3pcCe5FX0Jo+iD3kV44B5wEl0Pw48YLybAysYfwxkP+P/muX7hry8b2kn1EJeRSj5XhEcN6KAKUA7MB3YFjgc2A44BtgeOAHoAE4FRgNnATsAs4EdgYuAMcBcYCdgETCW40xnYDkwjvk/Yr6To46Z/3jIIeZ/uGS/1QYczX3Wx5C/WMj2GstxeRzbKQO4FDgeuBI4ke0yj3yj84E15Fdupj3Vy0VfdfG+JgF3AScDb2I6NwOnAe8ATgfWA2cAn+D1J4FzgP+gndW3aEf1OK+bfKkM3heK/tCX7dWPfMoUthvKJnh+qcBMns/m+XzgIMZ/EFLD+Pcw/jjIc4x/BeP/GeMvAUaTX5pA+6vdgZtYz07eB6tYr+XA0fSfRf9z6H8usAK4gHZbc4BraEd2Le+PdeR/XcLn4aVAiFbD+l8PvIZ81u3AjcDdjP85D7um2fhdCWmRD7QGfKA1wT3Qg3ZOg3ZOT9XOadaLoQHZOt2G++xeSAOkCeJYiz3NIVmQEsgVkL2QJyBH1gb5KsEjeASPH+/xfc7/LzsDtv90+wtH0/GNK+b3qcLNqaiE8RAtmbYWttD+AhSTWJ+rX6zEXmAr4MU1/x8vzf/HhXisx6bu1DlYnoMpKi8sdNOZmvrhKuFvGedRGA6xddcmSHpTuuNfCvTIn+P8FYtL3wkbayvCI61dIBG2PuFR1nBbCjDE7rBz3sk1B9MVfrtBcpD+DofmNofTjmlfI9KYJnTOrdWJ6vPMdSI81vfEUL9s8AUUewP+O11DJXrOL+aLJZhFpRV+9wLUhgQ219LSXoCZVu98/Qf5cnjnq7K8pBV7Pp5G3iYwb0cVeTuGvCV55o1LVlu13+Np5M9o0wZ2iCiIgW/BX7pX/gqrXVZ5/OcLYT1sAxQXVGvqtdT0a67TXdgx8HlGlodzbpxnZFpyGzjD1G2Q4VVGLOQvrlhhNkEAZc04jTYw5n9Dw73z14T8ZXnnryRvuf97KusM5MngEkQwgH76MfKU65Un8FMCqKfc08iTcZ8Pi1C3o9M7TzBSEPh97jyNvBn19bRn3lhfNZ55E4Zn/ddXzWnkyaivVGY=
*/