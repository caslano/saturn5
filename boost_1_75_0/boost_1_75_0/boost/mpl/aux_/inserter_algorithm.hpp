
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
UVonw/095T3C1IWmP3uJZKelcEgbKZSNThDRcHk/DuJHvCfsjc0iHDo/d/PBQRK/Rq/oLAZmOo3RxQo+/uEDPCW4ZPCqbbFgBazZtC1BbfIdxipcTFjWwXL2PKQwTLCkq1a6tjrR1OeM1YEq/9+k/vdPmmbPZI2f52O3SQ4l+W24Nhg1cr98PcH1S4v4I3fBPhonQNDWdRFNvK9PjkLoJyAVZoZysXNL4reN+Tld2znaFTUuwf9a1elWArejdRGlIe7mYMJRGjkApE26dV9+WExAw94rgfolZiCPH6vXHvd1btDPaaTk8+9ghC5id55qlbg7f80MlwQ/FoC5yYsUogvDgv0VCs4omaEMU9lsaG/8Ir7/2IefkS13avx8+R0k7jm8ajb6gylD5MOpRNgRXHfaJVZ/VvFI0kiMtBh14MlDU3VBpGhAOh7qpbVIlT0naRE9JF989FY42BBpYDH7XlUqyujqQkyw02GbX2BJrMo5ShDYHEsL25Rj6QvNCi2Jg+25JcYFP9y/INmNEIAcHnllPCNQrzc9ISHsP05Qsrht5PJWn8xEr9hRQ4nEZsDoCsMmogMKbCA2GoEf/WjGAdcjUWvYoDkQVHOJ3VooeBF8MrzBgPgK3NJH/wCcQ+lQGMCUSol3AKnUkUUe4N7BvOrFUfKKswSQbNShForGcBoeqNA9bjbpZyUcH97btLDEhLh7VVSfLZyjMGHj
*/