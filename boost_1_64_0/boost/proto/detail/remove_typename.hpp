//==============================================================================
//         Copyright 2003 - 2011  LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011  LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011         Eric Niebler
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_PROTO_PREPROCESSOR_REMOVE_TYPENAME_HPP_INCLUDED
#define BOOST_PROTO_PREPROCESSOR_REMOVE_TYPENAME_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the BOOST_PROTO_REMOVE_TYPENAME macro
 */
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>

//==============================================================================
// Boost.Preprocessor author P. Mensodines confirmed on an Boost email thread
// (subject ``check if a token is a keyword (was "BOOST_PP_IS_UNARY()")'')
// that it is OK to used `PP_IS_UNARY()` to check if tokens match predefined
// "keyword" as it is done by the macros below (even if `PP_IS_UNARY()` is
// technically only part of Boost.Preprocessor private API).
//==============================================================================

//==============================================================================
// `checking_prefix ## tokens` expand to unary (e.g., `(1)`) iff `tokens` start
// with keyword to check.
//==============================================================================
#define BOOST_PROTO_DETAILS_KEYWORD_FACILITY_IS_FRONT(T, CHECKING_PREFIX)                           \
    BOOST_PP_IS_UNARY(BOOST_PP_CAT(CHECKING_PREFIX, T))                                             \
    /**/

//==============================================================================
// `is_front_macro(tokens)` is 1 iff `tokens` start with keyword to remove.
// `removing_prefix ## <keyword-to-remove>` must expand to nothing.
//==============================================================================
#define BOOST_PROTO_DETAILS_KEYWORD_FACILITY_REMOVE_FRONT(TOKENS, IS_FRONT_MACRO, REMOVING_PREFIX)  \
    BOOST_PP_EXPAND( /* without EXPAND doesn't expand on MSVC */                                    \
        BOOST_PP_IIF(                                                                               \
            IS_FRONT_MACRO(TOKENS)                                                                  \
          , BOOST_PP_CAT                                                                            \
          , TOKENS BOOST_PP_TUPLE_EAT(2)                                                            \
        )(REMOVING_PREFIX, TOKENS)                                                                  \
    )                                                                                               \
    /**/

#define BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_IS_typename (1) /* unary */
#define typename_BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_IS (1) /* unary */
#define BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_REMOVE_typename /* nothing */
#define typename_BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_REMOVE /* nothing */

#define BOOST_PROTO_DETAILS_KEYWORD_IS_TYPENAME_FRONT(TOKENS)                                       \
    BOOST_PROTO_DETAILS_KEYWORD_FACILITY_IS_FRONT(TOKENS, BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_IS_) \
    /**/

//==============================================================================
/*!
 * \ingroup preprocessor
 * For any symbol \c X, this macro returns the same symbol from which a potential
 * leading \c typename keyword has been removed. If no typename keyword is present,
 * this macros evaluates to \c X itself without error.
 *
 * The original implementation of this macro is from Lorenzo Caminiti.
 *
 * \param X Symbol to remove \c typename from
 */
//==============================================================================
#define BOOST_PROTO_REMOVE_TYPENAME(X)                                                              \
    BOOST_PROTO_DETAILS_KEYWORD_FACILITY_REMOVE_FRONT(                                              \
        X                                                                                           \
      , BOOST_PROTO_DETAILS_KEYWORD_IS_TYPENAME_FRONT                                               \
      , BOOST_PROTO_DETAILS_KEYWORD_TYPENAME_REMOVE_                                                \
    )                                                                                               \
    /**/

#endif

/* remove_typename.hpp
AvuyjI5A/yjijBqocIpjIhU2bxdR+4nc1RfcXJLIZB1uiJlHyzIol0DLAeLXEF+buXQc4tRpHLa92MJnRHkBoGgc0YN1pTxOraAAq+hKtCeX5NJ69yiqiqtFgepWY68Ii4S0zyuaL7oHz42/7KoR5MzvKgc/4OY3HWE1AvoWOq2vpbuu/LMrzSL1m4MX2hY0Md/LBRqp4kQ+lRiNPI1FW4mpDmWEDmMmPXeWIGZzsqJrLl1FaP6L3sAL56YwwhyqnvEok+TZTkM3H/J5C5H4GP5LneSYzlTYMUbQfAF2Xf3tTCFe/adE5ghVmJIGfMRLlQlBM9PSy8vl75zmi/Whet5DPSd/zyR6Gzl+HSH0Rf5gkmXNivupXxHFymx7RYsQF5dieYDmINVe1MgcsPsxwLvdkQvrT9I/wx/sI/LAKYI2lYxsOfpbzcOgFEAUNDlDlRI9Dt/pgGb9MZhQPYO2cKYKJrhxWG7fWn7cnFW8+ek+wEgdgdID8LD/nLSr9ohULwSUjtAcedxnxiL5YXN0hld53roCzl/6odTOCjgB5mNkDgeoKY6khqgK8w==
*/