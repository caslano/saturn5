
#ifndef BOOST_MPL_COPY_IF_HPP_INCLUDED
#define BOOST_MPL_COPY_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Operation
    , typename Predicate
    >
struct copy_if_op
{
    template< typename Sequence, typename T > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : eval_if<
              typename apply1<Predicate,T>::type
            , apply2<Operation,Sequence,T>
            , identity<Sequence>
            >
    {
#else
    {
        typedef typename eval_if<
              typename apply1<Predicate,T>::type
            , apply2<Operation,Sequence,T>
            , identity<Sequence>
            >::type type;
#endif
    };
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct copy_if_impl
    : fold<
          Sequence
        , typename Inserter::state
        , protect< aux::copy_if_op<
              typename Inserter::operation
            , Predicate
            > >
        >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct reverse_copy_if_impl
    : reverse_fold<
          Sequence
        , typename Inserter::state
        , protect< aux::copy_if_op<
              typename Inserter::operation
            , Predicate
            > >
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, copy_if)

}}

#endif // BOOST_MPL_COPY_IF_HPP_INCLUDED

/* copy_if.hpp
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
*/