// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPLIT_ARGS_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPLIT_ARGS_HPP

#include <boost/preprocessor/tuple/elem.hpp>

// Accessor macros for the split_args tuple.
#define BOOST_PARAMETER_SPLIT_ARG_REQ_COUNT(x) BOOST_PP_TUPLE_ELEM(4, 0, x)
#define BOOST_PARAMETER_SPLIT_ARG_REQ_SEQ(x) BOOST_PP_TUPLE_ELEM(4, 1, x)
#define BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(x) BOOST_PP_TUPLE_ELEM(4, 2, x)
#define BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(x) BOOST_PP_TUPLE_ELEM(4, 3, x)

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/seq/push_back.hpp>

// Helper macros for BOOST_PARAMETER_FUNCTION_SPLIT_ARGS.
#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_required(s_a, arg)                \
    (                                                                        \
        BOOST_PP_INC(BOOST_PARAMETER_SPLIT_ARG_REQ_COUNT(s_a))               \
      , BOOST_PP_SEQ_PUSH_BACK(BOOST_PARAMETER_SPLIT_ARG_REQ_SEQ(s_a), arg)  \
      , BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(s_a)                             \
      , BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(s_a)                               \
    )
/**/

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_deduced_required(split_args, arg) \
    BOOST_PARAMETER_FUNCTION_SPLIT_ARG_required(split_args, arg)
/**/

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_optional(s_a, arg)                \
    (                                                                        \
        BOOST_PARAMETER_SPLIT_ARG_REQ_COUNT(s_a)                             \
      , BOOST_PARAMETER_SPLIT_ARG_REQ_SEQ(s_a)                               \
      , BOOST_PP_INC(BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(s_a))               \
      , BOOST_PP_SEQ_PUSH_BACK(BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(s_a), arg)  \
    )
/**/

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_deduced_optional(split_args, arg) \
    BOOST_PARAMETER_FUNCTION_SPLIT_ARG_optional(split_args, arg)
/**/

#include <boost/parameter/aux_/preprocessor/impl/argument_specs.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG(s, split_args, arg)               \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_FUNCTION_SPLIT_ARG_                                  \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(arg)                                \
    )(split_args, arg)
/**/

#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/seq.hpp>

// Expands from the flattened BOOST_PARAMETER_FUNCTION et. al. arg sequence to
// the tuple (required_count, required_args, optional_count, optional_args).
#define BOOST_PARAMETER_FUNCTION_SPLIT_ARGS(args)                            \
    BOOST_PP_SEQ_FOLD_LEFT(                                                  \
        BOOST_PARAMETER_FUNCTION_SPLIT_ARG                                   \
      , (0, BOOST_PP_SEQ_NIL, 0, BOOST_PP_SEQ_NIL)                           \
      , args                                                                 \
    )
/**/

#endif  // include guard


/* split_args.hpp
Gfp9naB70teae7huE89cLukef7Oo2mYGGg/ca8Nj9XbAJKjTLOsz0lYn+gMs/Qv9IYhcl1gXv87LunS/jVMdsrHDffG5VEsnVyDtlKUNVyrbru7Jg6zm+kP/mt01le8v2lW1Cp/y3G8EwljfOvjODxrjErFrgtGYpU//6Mav/cFvnGFpfv0cMTQY40AcBreCVrJDu4IgtY2EKv5hqh+xE71Gglco2jyzdl9lAkYWURdRF25MbRc2vM24Atfx6R0g/FNE72829JJtcy+koR/oFkEEiME0YW9N+OrNFIiM8jOyP3hvg/8iOQdH/JNhF3GXjAoJ2Sw75lzmOPhI7FcAHybugPOADmITk4Q+Eq+QRimLERZD6Qwc6Tbuyl9Ju6ugOII0AMCX4A7BgrsTSHC3C65BEzQkuLsssoEEdwguu3gI7i7B3WVxD4u7LezucX51dVf3cFXzMg8z0/13z9/1Vc/Uj63ZxX9GfZdLgC/7UmHjJfMGrjEqHqs55VIucctHHAn85c0P0BC4C6EcYVi+y4v+jefGwSPxobKpnQux9WfnTl8dNeKkAa2J25Bl0q1CPoAVgWkE4uVJF8aZlD9NCZ4B0fp0x7nruygBYUirbpI/8AdEJ+/+yzV5exWfLxjLkVbWD7Tb0IG9sCHmT7Emg/1adick5s+1yB0Uq/25TO22SrmKyLZwduXRLkcah6NEHk5TdqkNyIfbyv8o
*/