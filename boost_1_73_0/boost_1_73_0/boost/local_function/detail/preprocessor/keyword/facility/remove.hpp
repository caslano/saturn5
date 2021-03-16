
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
2NyUxhp6ykkzPjIbBL/KnmCluuSW/Y2FenKQkQdswQw6dlno2GWhdvnp0uK92kc59oTsoKOlpjGce9tOvWfGtlvb6cVMvVyl6aVbiF6MbZa2XfoPBGeveXeawNlgPVDjQAq4Q7bhoLlR60CqUs17hile0zamWOm3GOcJMzuglutlUMpdZlDK4WmE+w6jDUo5RRZAG7HrA2RhslwqC2hde7Iwx7Wgum42yUMa0/0LYeitLMDQk9YRDL2F+Q09SQM=
*/