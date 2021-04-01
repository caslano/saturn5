
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
ydif3EkQC8+AlZIkSwYGdBMBaZNwOTCsGSU7JPcoeYQTwmSp9hTzXy43c66SiBiqn/EORphHu9dhdE7zvfT/57aGHAt/sxvWuLXDVc5PZQ/KUTuBc5pJaT18hHRUGwx/snVy3qNB/UTFoalPUxvEcdiet80pEpra05cxksex+JUqViiMaE6F4FS5/7niBxXa96YM26dvNY5HJoBOnY0XjEjPs+0XrXrF8yLjYZ93SJixCufpr7d1Dh8x/kc4H1He7VO4X4a5c2BDfA0vzm1+LHFNUCWRjEsV7pg4kYky6uG3zljOKhg2RwnYaTbyVnX61DV95QUff1bhryF5bI6gQGiEQ+MRVs7NFVs9vo8fTAM7lk+hOnvvPTez525bxQUG/3ka8vY7SwL0G2JrzzPrfXZhfru0E2fTRwGNf3h+6cJ+L4froxiAhzdSYZ7Z5kgL7jTCrFMT3KBSQC2cuttUs2PKqqBxCpFh7hTES8ts+UMFIhVoPx5brYqrDNYDfLKi7HZ6EvDOzqH+oza+7lEdQkc8ULtILHbBUTv23mx3FDFIb0xeK7Ul0oxrqA==
*/