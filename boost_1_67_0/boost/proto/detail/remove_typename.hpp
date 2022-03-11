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
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
*/