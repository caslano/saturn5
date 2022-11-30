
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
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
*/