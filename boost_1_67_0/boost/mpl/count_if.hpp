
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
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
*/