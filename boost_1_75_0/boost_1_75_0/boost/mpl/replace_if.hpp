
#ifndef BOOST_MPL_REPLACE_IF_HPP_INCLUDED
#define BOOST_MPL_REPLACE_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
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

#include <boost/mpl/transform.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate, typename T >
struct replace_if_op
{
    template< typename U > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >
    {
#else
    {
        typedef typename if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >::type type;
#endif
    };
};


template<
      typename Sequence
    , typename Predicate
    , typename T
    , typename Inserter
    >
struct replace_if_impl
    : transform1_impl<
          Sequence
        , protect< aux::replace_if_op<Predicate,T> >
        , Inserter
        >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename T
    , typename Inserter
    >
struct reverse_replace_if_impl
    : reverse_transform1_impl<
          Sequence
        , protect< aux::replace_if_op<Predicate,T> >
        , Inserter
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, replace_if)

}}

#endif // BOOST_MPL_REPLACE_IF_HPP_INCLUDED

/* replace_if.hpp
orPhdL2kx+aEAU+H/kXXTbJzz+IWadznGMRYG2yLvhDybxJqbQ1GiW346BGaUQyE4ze49VUdKsXoNNzhfbIS01bxuVUXJrY+rWZp9vz6rvO9+/YOR+Itsb1CwzN975n1V76bWf0yc+II1lOySqr8JZKiKK9kjtPi4WybZneRmghq8WBdXZusIm5zL7S7SETM3F5r+m6LP/3gn3MGUcM9kWJoU+Ox0e2L9dIha+4YLmQyBxMxDqfeNbIn6TM60BtRazNsd4X4cseEa2eUyioWGwDXWXJLl6hKl6gPKw7kDjtSf7IqjivtOjMaNYx7rh50rID1J7dWZt7xhCNXH5kf6HbeFU25w/VuFA8Tx0nFti6WWc4q6c2Uybv/AuVsV1XhuEXFERushGmyPUJnr9OhTSk6XWUblBBv6eEicqYWLM4yiLjirsuEw+D5VDRvqlzM7zCgOhutxkNqqCkNjr/VD7aMHNhHaXEU6dIZXKUaauW3wqsQqvUTiJMT1kZUhTIX7e+GEMYMTuI75YRShU/8rnfGMkC9cMNPfzx2tniolS6XK81zpO57KxE6V2bmibic4GWn/y0A9LoVBrhi6RB7+rKIzOewg0pJFIG5ac0dfYZpq4driT7arN+JPf2AI9dB1ZGFsmhCToQeL53CEEoEhFWIQGv6KWiXec0nEyvlf2E7ipt7MZb36KlhqGl6yZeLx92ZiyJtxQCN+q4U
*/