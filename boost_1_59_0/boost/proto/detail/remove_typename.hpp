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
+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
*/