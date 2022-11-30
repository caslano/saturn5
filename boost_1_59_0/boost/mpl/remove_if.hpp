
#ifndef BOOST_MPL_REMOVE_IF_HPP_INCLUDED
#define BOOST_MPL_REMOVE_IF_HPP_INCLUDED

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
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Pred, typename InsertOp > struct remove_if_helper
{
    template< typename Sequence, typename U > struct apply
    {
        typedef typename eval_if<
              typename apply1<Pred,U>::type
            , identity<Sequence>
            , apply2<InsertOp,Sequence,U>
            >::type type;
    };
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct remove_if_impl
    : fold<
          Sequence
        , typename Inserter::state
        , protect< aux::remove_if_helper<
              typename lambda<Predicate>::type
            , typename Inserter::operation
            > >
        >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct reverse_remove_if_impl
    : reverse_fold<
          Sequence
        , typename Inserter::state
        , protect< aux::remove_if_helper<
              typename lambda<Predicate>::type
            , typename Inserter::operation
            > >
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, remove_if)

}}

#endif // BOOST_MPL_REMOVE_IF_HPP_INCLUDED

/* remove_if.hpp
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
*/