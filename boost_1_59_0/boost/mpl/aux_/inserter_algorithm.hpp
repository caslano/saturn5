
#ifndef BOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED
#define BOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/preprocessor/default_params.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   define BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(arity, name) \
BOOST_MPL_AUX_COMMON_NAME_WKND(name) \
template< \
      BOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct name \
    : aux::name##_impl<BOOST_MPL_PP_PARAMS(arity, P)> \
{ \
}; \
\
template< \
      BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), typename P) \
    > \
struct name< BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P),na > \
    : if_< has_push_back< typename clear<P1>::type> \
        , aux::name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::reverse_##name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
\
template< \
      BOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct reverse_##name \
    : aux::reverse_##name##_impl<BOOST_MPL_PP_PARAMS(arity, P)> \
{ \
}; \
\
template< \
      BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), typename P) \
    > \
struct reverse_##name< BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P),na > \
    : if_< has_push_back<P1> \
        , aux::reverse_##name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
BOOST_MPL_AUX_NA_SPEC(arity, name) \
BOOST_MPL_AUX_NA_SPEC(arity, reverse_##name) \
/**/

#else

#   define BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(arity, name) \
BOOST_MPL_AUX_COMMON_NAME_WKND(name) \
template< \
      BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), typename P) \
    > \
struct def_##name##_impl \
    : if_< has_push_back<P1> \
        , aux::name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::reverse_##name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
\
template< \
      BOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct name \
{ \
    typedef typename eval_if< \
          is_na<BOOST_PP_CAT(P, arity)> \
        , def_##name##_impl<BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P)> \
        , aux::name##_impl<BOOST_MPL_PP_PARAMS(arity, P)> \
        >::type type; \
}; \
\
template< \
      BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), typename P) \
    > \
struct def_reverse_##name##_impl \
    : if_< has_push_back<P1> \
        , aux::reverse_##name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
template< \
      BOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct reverse_##name \
{ \
    typedef typename eval_if< \
          is_na<BOOST_PP_CAT(P, arity)> \
        , def_reverse_##name##_impl<BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P)> \
        , aux::reverse_##name##_impl<BOOST_MPL_PP_PARAMS(arity, P)> \
        >::type type; \
}; \
BOOST_MPL_AUX_NA_SPEC(arity, name) \
BOOST_MPL_AUX_NA_SPEC(arity, reverse_##name) \
/**/

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED

/* inserter_algorithm.hpp
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
*/