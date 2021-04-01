
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_HPP_

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/cat.hpp>

// PRIVATE //

// From PP_EXPAND (my own reentrant version).
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC() && \
        ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_(x) \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_I_(x)
#else
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_(x) \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_OO_((x))
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_OO_( \
            par) \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_I_ ## par
#endif
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_I_(x) x

// PUBLIC //

// `is_front_macro(tokens)` is 1 if `tokens` start with keyword to remove.
// `removing_prefix ## <keyword-to-remove>` must expand to nothing, else 0.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT( \
        tokens, is_front_macro, removing_prefix) \
    /* without EXPAND doesn't expand on MSVC */ \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_( \
        BOOST_PP_IIF(is_front_macro(tokens), \
            BOOST_PP_CAT \
        , \
            tokens BOOST_PP_TUPLE_EAT(2) \
        )(removing_prefix, tokens) \
    )

// `is_back_macro(tokens)` is 1 iff `tokens` end with keyword to remove.
// `<keyword-to-remove> ## removing_postfix` must expand to nothing, else 0.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK( \
        tokens, is_back_macro, removing_prefix) \
    BOOST_PP_IIF(is_back_macro(tokens), \
        BOOST_PP_CAT \
    , \
        tokens BOOST_PP_TUPLE_EAT(2) \
    )(tokens, removing_postfix)

#endif // #include guard


/* remove.hpp
FGpx08WheTHVuSlfcy/sfoMiEswXlXun0k2T6376jrKUH8j8ECCqvU+mYZLbz+ZfHi7tokql6DQ7WzeXMaZwFMMlfLbqE5Z0k3PBI43uY0PMGHdyi1+zdUeb4roqbRwrh/JVghnGXtwaZjA0s7pBmzoU7PAuDhNENmh1Xlwb8XGSMhEqXNNaNxUUP73MwsXZZ96WplZ29FMt749r7wIDQRDl4APwT8Cwr8Xtn8p5DKqqUbb5Zq2QECM2MerU/DTQ2b9bpXvRy79Q3edi36hratbAJWCaDyHZWf0O3mfiI06DPt7MT/I1RkyTDUKd/ew7PxDTD1wQJ47aTJi6D03n3Sxz/kwLmdoMm22YzRyexx8oV/W5EFvOmZchQVKDKh4AlQPbAI43S4u/0dGWFxGdNjdQ0nfA1AQbuZ9vPy68KRXLqASS38aoWkn/qPylR2FEfvEKqdLMgVT10zH0HCTy9WczjtP49i/mwQ/bZGZsivU33+EWIvmLhp0bgyYyZXp9ekNGWwCcyn/6td6jDfSMOjRiT4PD2Q5l5CQnYPqpI30FauNoKuloTaXsMw==
*/