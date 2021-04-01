
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
wxjGpbh07f13+TIl/mJW2i/kQBvdQHfwv841A2QvBYsoPYNhKCRJxnI3QH90Um3hY3l+oiViXfbHiJonMSqlcrfYG+Ad8AQtYTzDC4R2oVt5xtBeyyug2iIOp4dnjKztuYE7fQ1JIZX2b4ihVq59ppJmEegApk2v6NWTOJPh4ntXf+vP1GjSGr+w0dZNQ+oWpF0acCTDr24MNZNON6XEN0hG7M9tytHK1i52tCEBJP5YKorfkJQ435+/qvNJl6AKb2lYJPE0UBRjEmzCjCxylG2YYx5IeRw7DV25F1OhjJINacDMiWUqRM9O0JPtO48b9OUscd9ESFxcuWeX4+BNUxEJLeCueCEQ6NQdPMiRLeyS325r+N6LKwnL1hBnmnVX0NphDJfM9FC+K3TFaHK4ylJVzQnFQen029DnoxMopxS8iwr7llNoYX2ptBPS9UCsGxMkerzxGJbfdcoArN50aCRwGMx8btEsZbq94BOQzAtut34I6hV+0Y1914OIa/sg4Y0QeEqzLh0vFs0zV+e2g1U7jAi/VNTIj3UlsxOnCPgnWcs/hi3eFqm94A==
*/