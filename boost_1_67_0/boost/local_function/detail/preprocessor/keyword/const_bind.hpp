
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_HPP_

#include <boost/local_function/detail/preprocessor/keyword/bind.hpp>
#include <boost/local_function/detail/preprocessor/keyword/const.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/add.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_BIND_IS_bind (1) /* unary */
#define bind_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_BIND_IS (1) /* unary */
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_BIND_REMOVE_bind /* nothing */
#define bind_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_BIND_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT_(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_BIND_FRONT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_REMOVE_FRONT(tokens))

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT(tokens) \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_FRONT(tokens),\
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(tokens)
        
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_BACK_(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BACK( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_BIND_REMOVE_BACK(tokens))

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONDT_BIND_BACK(tokens) \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_BIND_BACK(tokens) \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_BACK_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(tokens)

// Remove.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_BIND_REMOVE_FRONT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_REMOVE_FRONT(tokens))

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_REMOVE_BACK( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_BIND_REMOVE_BACK(tokens))

// Add.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_ADD_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT, \
            const bind)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_ADD_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_BACK, \
            const bind)

#endif // #include guard


/* const_bind.hpp
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
*/