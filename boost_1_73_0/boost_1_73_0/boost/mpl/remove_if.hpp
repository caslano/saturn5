
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
hcMEshc8h/AKHvQO4jAKIbpMLq+SMIT77xnzTAl0DgLbD3ghNsjmg8QEuNHa8ejL5zAM4wv36q6l1pVVDsd7tOxW1zVKD5WVtshYL8sHg159p7HQpmdR9Zr0WrVtKoQji08MLTJKhLfaO45/sRyT6G89DnMo0SAUqkawrfXE/2SYfDisXTDHeu3KBD7FjM0KcEOKDUpUO8zPaQbhUMCjbKAqbjA/qI8H+bJEuXkfVXuPaR7Sm/LhkNDZua1UF9+fHdkPCOAlTFjpXEPwwxDSWmzR14e4c0X8DlrlSngWZF5bBx2CurkRxmsRdQ62ErYEVUM3u0WHxlIs7oNBKvV2SzBPl3B+Ol2sstkyOe14lovH7FqX47YULug7YNxlqasVBHMS97abfgf95OsJjSr20LkGURBjn6FuJ5TCwjNiDSe21O6EpbseSwEao52WupowunyA/4n2UPoRm5LjBH7TO2I/KGXBzZrUUMO8mIqfPt09rmaLhxG7kRIbmj7jZyM28kx/7b7/y5fyo8uUv1nnx0v5J1BLAwQKAAAACAAtZ0pSc0646qQBAADUAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE4OFVUBQABtkgkYL1TXUvrQBB9H8h/GJS+CHGbK4KE
*/