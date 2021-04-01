
#ifndef BOOST_MPL_COUNT_IF_HPP_INCLUDED
#define BOOST_MPL_COUNT_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate >
struct next_if
{
    template<
          typename N
        , typename T
        >
    struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : eval_if<
              typename apply1<Predicate,T>::type
            , next<N>
            , identity<N>
            >
    {
#else
    {
        typedef typename eval_if<
              typename apply1<Predicate,T>::type
            , next<N>
            , identity<N>
            >::type type;
#endif
    };
};

} // namespace aux


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct count_if
    : aux::msvc_eti_base< typename fold<
          Sequence
        , integral_c<unsigned long,0>
        , protect< aux::next_if<Predicate> >
        >::type >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,count_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(2, count_if)

}}

#endif // BOOST_MPL_COUNT_IF_HPP_INCLUDED

/* count_if.hpp
VtuFINasvgG8108hDGgcmATtCXk1HDsikd22P5h4pCD8Y37o+ttlfMJHeh6LjvZuUZ9nW7a0PCXXQAD60CsCLQkhLSsiTB4bBUe+yKc4MDZLfGvLIBPG3AKDN5mR279QFOTrPUDGSag5RoOYFe7ijNUvmsSuz0nNP/rHn+clNXC4mCWSZVbkp+TmPIllAihwTV19qNSVw0t9PWLEMQIZPDjzvevlA+/8FzkWUwtthC0U1i0Oo4eyxQhNa74qmGwpnMfZV5eT7iBG20lmUR70EEzRXqmkL9MXnuX08bnNhN62VHr5gaW43+cGBI43WMS+38VkVzwJVDkN3Wa9oHWitcI1YWU181fLSeDXsrDi91L+CY1E2jn/zKYdyLsG7n686iMJr96ZePoIo9MismtVpderdombeeqMeq1u9YJG/kvLtdn+TxU+ZhqgsgNCN7kiVkNq9ZNfhvad5DWOp3ZI3lhxzbLHeKTvZsYkeE+VJUw76kEPSG6EYAziC8/lqpaiBoeZ+YaZ83JtynHhLa/Pnuh3PSiLZQbIhTHg8aytdxoIK4PcCThL+MmPrw==
*/