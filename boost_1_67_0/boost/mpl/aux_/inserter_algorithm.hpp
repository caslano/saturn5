
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