
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/expr_if.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/cat.hpp>

#if !defined(AUX778076_COUNT_ARGS_PARAM_NAME)
#   define AUX778076_COUNT_ARGS_PARAM_NAME T
#endif

#if !defined(AUX778076_COUNT_ARGS_TEMPLATE_PARAM)
#   define AUX778076_COUNT_ARGS_TEMPLATE_PARAM typename AUX778076_COUNT_ARGS_PARAM_NAME
#endif

// local macros, #undef-ined at the end of the header

#if !defined(AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES)

#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>

#   define AUX778076_COUNT_ARGS_REPEAT BOOST_MPL_PP_REPEAT
#   define AUX778076_COUNT_ARGS_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          AUX778076_COUNT_ARGS_ARITY \
        , param \
        ) \
    /**/

#else

#   include <boost/preprocessor/enum_shifted_params.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/inc.hpp>

#   define AUX778076_COUNT_ARGS_REPEAT BOOST_PP_REPEAT
#   define AUX778076_COUNT_ARGS_PARAMS(param) \
    BOOST_PP_ENUM_SHIFTED_PARAMS( \
          BOOST_PP_INC(AUX778076_COUNT_ARGS_ARITY) \
        , param \
        ) \
    /**/

#endif // AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES


#define AUX778076_IS_ARG_TEMPLATE_NAME \
    BOOST_PP_CAT(is_,BOOST_PP_CAT(AUX778076_COUNT_ARGS_PREFIX,_arg)) \
/**/

#define AUX778076_COUNT_ARGS_FUNC(unused, i, param) \
    BOOST_PP_EXPR_IF(i, +) \
    AUX778076_IS_ARG_TEMPLATE_NAME<BOOST_PP_CAT(param,BOOST_PP_INC(i))>::value \
/**/

// is_<xxx>_arg
template< AUX778076_COUNT_ARGS_TEMPLATE_PARAM >
struct AUX778076_IS_ARG_TEMPLATE_NAME
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<>
struct AUX778076_IS_ARG_TEMPLATE_NAME<AUX778076_COUNT_ARGS_DEFAULT>
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

// <xxx>_count_args
template<
      AUX778076_COUNT_ARGS_PARAMS(AUX778076_COUNT_ARGS_TEMPLATE_PARAM)
    >
struct BOOST_PP_CAT(AUX778076_COUNT_ARGS_PREFIX,_count_args)
{
    BOOST_STATIC_CONSTANT(int, value = AUX778076_COUNT_ARGS_REPEAT(
          AUX778076_COUNT_ARGS_ARITY
        , AUX778076_COUNT_ARGS_FUNC
        , AUX778076_COUNT_ARGS_PARAM_NAME
        ));
};

#undef AUX778076_COUNT_ARGS_FUNC
#undef AUX778076_IS_ARG_TEMPLATE_NAME
#undef AUX778076_COUNT_ARGS_PARAMS
#undef AUX778076_COUNT_ARGS_REPEAT

#undef AUX778076_COUNT_ARGS_ARITY
#undef AUX778076_COUNT_ARGS_DEFAULT
#undef AUX778076_COUNT_ARGS_PREFIX
#undef AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES
#undef AUX778076_COUNT_ARGS_TEMPLATE_PARAM
#undef AUX778076_COUNT_ARGS_PARAM_NAME

/* count_args.hpp
Aj4+dgKfNqBRWbk6r+NOEjfzVZ7ulV9fF2ShBU9FuMm15IcUTLfD7DTrQD/aTmXCM4uPL1pgYzsreysTiPGgIc3q8Ji9FXD0uQmpWKPpm7T1/PLRsrgnWd4cWG+me7kz0Y3ylblyCJrhQHoJzYehlP9gRIpadxtxQWULRT14jzx7iX75MfcTpI/bBXPxFaW2LtQfIhJfdabQjmzYm8Pd/Xb5rOqRHXp94lVxP1peO8htW4X2GtnSVa7LRM/2Gq9RjWnEGbbohr7y0zQ+52dBFUmsq8yEDkTLpAL8WbiwH0Is8mG/6cY8QdPlooDQr6c57/7JIiionsGb9lHfVLCKlVr7Bj4suP/6uiX5GDol2f7SN+qhkX/h/JvENk+v4nU4Ywk5/JXkcw9WkLMWFCwLByQAIw5DCOHdVjb29cI2EcyzCRdj4vbJC3vydycOV489s53Cl1Va/qGSUOjUhrZBSODKgxAFfCK0B7eqgB1PU8zTIEiUJfDvrhPXsO1Dk5qDmOCLZXHfqqXRYeDooM+H25g7L4Hbk8u4Ta/nhTtH7AeUWrzqW+H8ifK8ybEFrNs8s+0s0gLEfW/kVhBOkOaWl4pnuy3gFfGnWxCi1RTW3R1y33feux8c5EIzB/6mp1YMtxWs0UTY7lP1TCE+H0b3tiEfDPD3Q3F9WOoHGeZ6crX2g4bxaSefQdAgHGNsL/TOvxJ2lTFxQEkYdxZb
*/